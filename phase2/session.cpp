#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Session {
  public:
    string sessionType;
    string transaction;
    string accountHolderName;
    bool accountHolderExist;
    void login();
    void getsessionType();
    bool validateAccountHolder();
};

/*
  login will read in the first transaction as std input and save it to transaction variable

  when the transaction is login the system will then call the method getsessionType

  return type none
  note: any invalid input for the first transaction will terminate the system
  and the terminal will output invalid input
*/
void Session::login() {
  cin >> transaction;
  if(transaction == "login"){
      getsessionType();
  }else{
      cout << "invalid input\n";
      exit(0);
  }
};

/*
  getsessionType will read in session type as std input and save it to 
  the variable sessionType

  var accountHolderExist -> used to save if the account holder name exist

  terminal output enter session type
  user enters standard or admin
    admin: will initiate transaction (not implemented yet)
    standard: terminal outputs enter account holder name
              user enters account holder name
              system will then validate account holder name

  return type none
  note: any invalid input for session type or an account that does not exist will 
  terminate the session
*/
void Session::getsessionType() {
  cout << "enter session type:\n";
  cin >> sessionType;
  if(sessionType == "standard"){
    cout << "enter account holder name\n";
    cin >> accountHolderName;
    accountHolderExist = validateAccountHolder();
  }else if (sessionType == "admin"){
    //getTransaction();
  }else{
      cout << "invalid input\n";
      exit(0);
  }
};


/*
  validateAccountHolder will validate if an account holder name is in the 
  current bank account file

  var line -> used to read file line by line
  var word[4] -> used to store each word in a line(account number, account name, account status, balance)
  var counter -> used to index word

  if account holder name exist
  return true

  return false 
  terminal outputs account not found
*/
bool Session::validateAccountHolder() {
  string line;
  ifstream reader("CurrentBankAccounts.txt");
  while (getline (reader, line)) {
    string word[4];
    int counter = 0;
    for(int i = 0; i < line.length(); i++){
      if(line[i] == '_'){
        counter++;
      }else if(line[i] == ' '){

      }
      else{
        word[counter] += line[i];
      }
    }
    if(word[1] == accountHolderName){
      reader.close();
      return true;
    }
  }
  cout << "account not found\n";
  reader.close();
  return false;
};

class Transaction {
  public:
  string currentTransaction;
  string transactionCode;
  string validTransactions[9];
  string currentPayee;
  string planType;
  string validPayees[3];
  string validPlans[2];
  string accountHolderName;
  string accountNumber;
  string accountNumberTo;
  string accountHolderNameTo;
  string sessiontype;
  Transaction(Session currentsession){
    validTransactions[0] = "logout";
    validTransactions[1] = "withdrawal";
    validTransactions[2] = "deposit";
    validTransactions[3] = "transfer";
    validTransactions[4] = "paybill";
    validTransactions[5] = "disable";
    validTransactions[6] = "delete";
    validTransactions[7] = "create";
    validTransactions[8] = "changeplan";
    validPayees[0] = "EC";
    validPayees[1] = "CQ";
    validPayees[2] = "FI";
    validPlans[0] = "NP";
    validPlans[1] = "SP";
    sessiontype = currentsession.sessionType;
    if(currentsession.sessionType == "standard"){
      accountHolderName = currentsession.accountHolderName;
    }else{
      accountHolderName = "";
    }
  };
  void getTransaction();
  bool validateTransaction();
  bool validatePayee();
  bool validatePlan();
  bool validateAccountNumber();
  bool logout();
  bool withdrawal();
  bool changeplan();
  bool deposit();
  bool transfer();
  bool paybill();
  bool disable();
  bool Delete();
  bool create();
  void startCurrentTransaction();
};

/*
  getTransaction will read in the transaction type as std input and
  save it to the currentTransaction variable and then validate the transaction

  terminal will output enter transaction type
  user enters transaction type

  return type none
*/
void Transaction::getTransaction(){
  cout << "enter transaction type\n";
  cin >> currentTransaction;
  validateTransaction();
};

/*
  validateTransaction will validate if the transaction currently
  entered by user is valid.

  if the current transaction is valid
  return true

  terminal will output invalid input for any incorrect transaction 
  and then call the method getTransaction

  note: method will never return false, it will always prompt until 
  a valid transaction is given
  Session terminates when logout transaction is called
*/
bool Transaction::validateTransaction(){
  for(int i = 0; i < 9; i++){
    if(currentTransaction == validTransactions[i]){
      return true;
    }
  }
  cout << "invalid input\n";
  getTransaction();
  return false;
};

bool Transaction::validatePlan(){
  cout << "enter account type (SP - student, NP - standard):\n";
  cin >> planType;
  for(int i = 0; i < 2; i++){
    if(planType == validPlans[i]){
      return true;
    }
  }
  cout << "unknown plan\n";
  validatePlan();
  return false;
}

bool Transaction::validatePayee(){
  cout << "enter the payee:\n";
  cin >> currentPayee;
  for(int i = 0; i < 3; i++){
    if(currentPayee == validPayees[i]){
      return true;
    }
  }
  cout << "invalid input\n";
  return false;
}

/*
  validateAccountNumber will validate if an account number is in the 
  current bank account file and matches the account holder name

  var line -> used to read file line by line
  var word[4] -> used to store each word in a line(account number, account name, account status, balance)
  var counter -> used to index word

  if account holder name and number both exist on the same line
  return true

  special case for when the transaction being processed is transfer,
  since it is the only transaction involving two account it will 
  check that the account number to transfer also exist. 
  return true

  return false 
  terminal outputs account number not found
*/
bool Transaction::validateAccountNumber(){
  string line;
  ifstream reader("CurrentBankAccounts.txt");
  while (getline (reader, line)) {
    string word[4];
    int counter = 0;
    for(int i = 0; i < line.length(); i++){
      if(line[i] == '_'){
        counter++;
      }else if(line[i] == ' '){

      }
      else{
        word[counter] += line[i];
      }
    }
    if(currentTransaction == "transfer" && accountNumberTo == word[0]){
      accountHolderNameTo = word[1];
      return true;
    }
    if(word[1] == accountHolderName && word[0] == accountNumber && accountNumberTo ==""){
      return true;
    }
  }
  cout << "account number not found\n";
  return false;
  reader.close();
};


/*
  startCurrentTansaction will initiate the users currentTransaction
  by checking validTransactions array and then calling the related
  transaction method

  No return type
*/
void Transaction::startCurrentTransaction(){
  if(currentTransaction == validTransactions[0]){
    logout();
  }else if(currentTransaction == validTransactions[1]){
    withdrawal();
  }else if(currentTransaction == validTransactions[2]){
    deposit();
  }else if(currentTransaction == validTransactions[3]){
    transfer();
  }else if(currentTransaction == validTransactions[4]){
    paybill();
  }else if(currentTransaction == validTransactions[5]){
    disable();
  }else if(currentTransaction == validTransactions[6]){
    Delete();
  }else if(currentTransaction == validTransactions[7]){
    create();
  }else if(currentTransaction == validTransactions[8]){
    changeplan();
  }
}
/***************************************************************************************************
tranfer transaction, validates account number (from), validates account number (to) and writes to
transaction file once user has entered transfer amount

var transferamount -> user inputs amount to transfer;

validates account(from) credentials
if false returns false

validates account(to) credentials
if false returns false

validates transferlimit for standard session is 1000
if false returns false

terminal prompts account number(from)
user inputs accountNumber(from)
terminal prompts account number(to)
user inputs accountNumber(to)
terminal prompts transfer amount
user inputs transfer amount
terminal outputs transfer successful

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
****************************************************************************************************/
bool Transaction::transfer(){
  string transferamount;
  cout << "enter account number(from):\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    cout <<"enter account number (to):\n";
    cin >> accountNumberTo;
    if(validateAccountNumber()){
      cout <<"enter transfer amount:\n";
      cin >> transferamount;
      if(::atof(transferamount.c_str()) > 1000 && sessiontype == "standard"){
        cout << "limit for standard transfer is 1000\n";
        accountNumberTo ="";
        accountHolderNameTo ="";
        return false;
      }
      cout <<"transfer successful\n";

      ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
        string tempname = accountHolderName;
      for(int i = accountHolderName.length(); i<20; i++){
        tempname += ' ';
      }
      for(int i = accountHolderNameTo.length(); i<20; i++){
        accountHolderNameTo += ' ';
      }
      string appendToTransaction = "02_"+tempname+"_"+accountNumber+"_"+transferamount+"_";
      string appendToTransaction2 = "02_"+accountHolderNameTo+"_"+accountNumberTo+"_"+transferamount+"_";
      writeTransactionFile << appendToTransaction << endl;
      writeTransactionFile << appendToTransaction2 << endl;
      writeTransactionFile.close();
      accountNumberTo ="";
      accountHolderNameTo ="";
      return true;
    }else{
      accountNumberTo ="";
      accountHolderNameTo ="";
      return false;
    }
  }
  accountNumberTo ="";
  accountHolderNameTo ="";
  return false;
}

bool Transaction::changeplan(){
  cout << "enter account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    if(validatePlan()){
      ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
      string tempname = accountHolderName;
      for(int i = accountHolderName.length(); i<20; i++){
        tempname += ' ';
      }
      if(planType == "NP"){
        cout << "account updated to non-student\n";
        string appendToTransaction = "08_"+tempname+"_"+accountNumber+"_00000.00_";
        writeTransactionFile << appendToTransaction << endl;
        writeTransactionFile.close();
        return true;
      }
      else if(planType == "SP"){
        cout << "account updated to student\n";
        string appendToTransaction = "08_"+tempname+"_"+accountNumber+"_00000.00_";
        writeTransactionFile << appendToTransaction << endl;
        writeTransactionFile.close();
        return true;
      }
    }
  }
  return false;
}
bool Transaction::deposit(){
  string depositAmount;
  cout << "enter account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    cout << "enter deposit amount\n";
    cin >> depositAmount;
    cout << "deposit successful\n";

    ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
    string tempname = accountHolderName;
    for(int i = accountHolderName.length(); i<20; i++){
      tempname += ' ';
    }
    string appendToTransaction = "04_"+tempname+"_"+accountNumber+"_"+depositAmount+"_";
    writeTransactionFile << appendToTransaction << endl;
    writeTransactionFile.close();
    return true;
  }
  return false;
}
/*

Paybill transaction, validates account number, validates payee and writes to
transaction file once user has entered payment amount

var paymentAmount -> user inputs amount to pay payee;

validates credentials
if false returns false

validates payee entry to ensure valid company currently [EC, CQ, FI]
if false returns false

terminal prompts amount
User inputs amount
Currently accepts any amount
terminal outputs confirmation

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/
bool Transaction::paybill(){
  string paymentAmount;
  cout << "enter the account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    if(validatePayee()){
      cout << "enter the amount:\n";
      cin >> paymentAmount;
      cout << "payment successful\n";

      ofstream writeTransactionFile("sessiontransactions.txt", ios::app);
      string tempname = accountHolderName;
      for(int i = accountHolderName.length(); i<20;i++){
        tempname += ' ';
      }
      string appendToTransaction = "03_"+tempname+"_"+accountNumber+"_"+paymentAmount+"_";
      writeTransactionFile << appendToTransaction << endl;
      writeTransactionFile.close();
      return true;
    }
    return false;
  }
  return false;
}
/*
withdrawal transaction, validates account number, and writes to
transaction file once user has entered withdrawal amount

var withdrawalamount -> user inputs amount for withdrawal;

validates account credentials
if false returns false

terminal prompts account number
user inputs account number
terminal prompts withdrawal amount
user inputs withdrawal amount
currently accepts any withdrawal amount
terminal outputs withdrawal successful

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/
bool Transaction::withdrawal(){
  string withdrawalamount;
  cout << "enter account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    cout << "enter withdrawal amount\n";
    cin >> withdrawalamount;
    cout << "withdrawal successful\n";

    ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
    string tempname = accountHolderName;
    for(int i = accountHolderName.length(); i < 20; i++){
      tempname += ' ';
    }
    string appendToTransaction = "01_"+tempname+"_"+accountNumber+"_"+withdrawalamount+"_";
    writeTransactionFile << appendToTransaction <<endl;
    writeTransactionFile.close();
    return true;
  }
  return false;
}

/*
logout transaction, writes the final line of the transaction file,
and will end the current session

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/
bool Transaction::logout(){
  ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
  // This tempname isn't strictly necessary but I figured for consistency
  // may as well add it.
  string tempname = accountHolderName;
  for(int i = accountHolderName.length(); i < 20; i++){
    tempname += ' ';
  }
  string appendToTransaction = string("00_")+tempname+string("_00000_")+string("00000.00_");
  writeTransactionFile << appendToTransaction <<endl;
  writeTransactionFile.close();
  return true;
};


bool Transaction::disable(){
  string d;
  cout << "enter account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    cout << "enter lowercase d to disable\n";
    cin >> d;
      if(d == "d"){
        cout << "disable successful\n";

        ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
        string tempname = accountHolderName;
        for(int i = accountHolderName.length(); i < 20; i++){
          tempname += ' ';
        }
        string appendToTransaction = string("05_")+tempname+string(accountNumber)+string("00000.00_")+string("_")+string("D");
        writeTransactionFile << appendToTransaction <<endl;
        writeTransactionFile.close();
        return true;
      }
      else{
        cout << "not lowercase d\n";
      }

  }
  return false;
}

bool Transaction::create(){
  string temp_name;
  string temp_num;
  string balance;

  cout << "enter account name\n";
  cin >> temp_name;

  cout  << "enter account number\n";
  cin >> temp_num;

  cout << "enter balance: \n";
  cin >> balance;

  ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
  for(int i = temp_name.length(); i < 20; i++){
    temp_name += ' ';
  }

  string appendToTransaction = string("07_")+string(temp_name)+string(temp_num)+string("_")+string(balance)+string("_");
  writeTransactionFile << appendToTransaction <<endl;
  writeTransactionFile.close();
  return true;

}

bool Transaction::Delete(){
  string withdrawalamount;
  cout << "enter account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){

    ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
    string tempname = accountHolderName;
    for(int i = accountHolderName.length(); i < 20; i++){
      tempname += ' ';
    }
    string appendToTransaction = "06_"+tempname+"_"+accountNumber+"_"+string("00000.00_");
    writeTransactionFile << appendToTransaction <<endl;
    writeTransactionFile.close();
    return true;
  }
  return false;
}

//This system is an automated teller machine terminal for simple banking transactions.
//The program is intended to run from the terminal where a session will be started and
//  process valid transactions for that session. A session will begin when 'login' is entered
//  and will end after logout.
//Input: currentBankAccount file
//Output: bankAccountTransaction file
int main()
{
    cout << "welcome to the banking system\n";
    Session newSession;
    newSession.login();
    if(newSession.accountHolderExist){
      Transaction newTransaction(newSession);
      newTransaction.getTransaction();
      while(newTransaction.currentTransaction != "logout"){
              newTransaction.startCurrentTransaction();
              newTransaction.getTransaction();
      }
      newTransaction.logout();
    }else{
      exit(0);
    }
    return 0;
}
