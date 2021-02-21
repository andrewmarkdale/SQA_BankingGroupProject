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

void Session::login() {
  cin >> transaction;
  if(transaction == "login"){
      getsessionType();
  }else{
      cout << "invalid input\n";
      exit(0);
  }
};

void Session::getsessionType() {
  cout << "enter session type:\n";
  cin >> sessionType;
  if(sessionType == "standard"){
    cout << "enter account holder name\n";
    cin >> accountHolderName;
    accountHolderExist = validateAccountHolder();
  }else if (sessionType == "admin"){
    //Do something
  }else{
      cout << "invalid input\n";
      exit(0);
  }
};

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
      return true;
    }
  }
  cout << "account not found\n";
  return false;
  reader.close();
};

// class User {
//   public:
//   string accountHolderName;
//   string accountBalance;
//   string accountNumber;
//   string accountStatus;
//   User(string number, string name, string status, string balance){
//     accountHolderName = name;
//     accountBalance = balance;
//     accountNumber = number;
//     accountStatus = status;
//   };
// };

class Transaction {
  public:
  string currentTransaction;
  string transactionCode;
  string validTransactions[9];
  string currentPayee;
  string validPayees[3];
  string accountHolderName;
  string accountNumber;
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
    if(currentsession.sessionType == "standard"){
      accountHolderName = currentsession.accountHolderName;
    }else{
      accountHolderName = "";
    }
  };
  void getTransaction();
  bool validateTransaction();
  bool validatePayee();
  bool validateAccountNumber();
  bool logout();
  bool withdrawal();
  bool deposit();
  bool transfer();
  bool paybill();
  bool disable();
  bool Delete();
  bool create();
  bool changeplan();
  void startCurrentTransaction();
};

void Transaction::getTransaction(){
  cout << "enter transaction type\n";
  cin >> currentTransaction;
  validateTransaction();
};


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
    if(word[1] == accountHolderName && word[0] == accountNumber){
      //User currentUser(word[0], word[1], word[2], word[3]);
      return true;
    }
  }
  cout << "account number not found\n";
  return false;
  reader.close();
};

void Transaction::startCurrentTransaction(){
  if(currentTransaction == validTransactions[0]){
    logout();
  }else if(currentTransaction == validTransactions[1]){
    withdrawal();
  }else if(currentTransaction == validTransactions[2]){
    deposit();
  }else if(currentTransaction == validTransactions[4]){
    paybill();
  }else if(currentTransaction == validTransactions[5]){
    disable();
  }else if(currentTransaction == validTransactions[6]){
    Delete();
  }else if(currentTransaction == validTransactions[7]){
    create();
  }
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
    for(int i = accountHolderName.length(); i<20; i++){
      accountHolderName += ' ';
    }
    string appendToTransaction = "04_"+accountHolderName+"_"+accountNumber+"_"+depositAmount+"_";
    writeTransactionFile << appendToTransaction << endl;
    writeTransactionFile.close();
    return true;
  }
  return false;
}
/*

Paybill transaction, validates account number, validates payee and writes to
transaction file once user has entered payment amount

*/
bool Transaction::paybill(){
  string paymentAmount;
  string payee;
  cout << "enter the account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    if(validatePayee()){
      cout << "enter the amount:\n";
      cin >> paymentAmount;
      cout << "payment successful\n";

      ofstream writeTransactionFile("sessiontransactions.txt", ios::app);
      for(int i = accountHolderName.length(); i<20;i++){
        accountHolderName += ' ';
      }
      string appendToTransaction = "03_"+accountHolderName+"_"+accountNumber+"_"+paymentAmount+"_";
      writeTransactionFile << appendToTransaction << endl;
      writeTransactionFile.close();
      return true;
    }
    return false;
  }
  return false;
}

bool Transaction::withdrawal(){
  string withdrawalamount;
  cout << "enter account number\n";
  cin >> accountNumber;
  if(validateAccountNumber()){
    cout << "enter withdrawal amount\n";
    cin >> withdrawalamount;
    cout << "withdrawal successful\n";

    ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
    for(int i = accountHolderName.length(); i < 20; i++){
      accountHolderName += ' ';
    }
    string appendToTransaction = "01_"+accountHolderName+"_"+accountNumber+"_"+withdrawalamount+"_";
    writeTransactionFile << appendToTransaction <<endl;
    writeTransactionFile.close();
    return true;
  }
  return false;
}

bool Transaction::logout(){
  ofstream writeTransactionFile("sessiontransactions.txt",ios::app);
  for(int i = accountHolderName.length(); i < 20; i++){
    accountHolderName += ' ';
  }
  string appendToTransaction = string("00_")+string(accountHolderName)+string("_00000_")+string("00000.00_");
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
        for(int i = accountHolderName.length(); i < 20; i++){
          accountHolderName += ' ';
        }
        string appendToTransaction = string("05_")+string(accountHolderName)+string(accountNumber)+string("00000.00_")+string("_")+string("D");
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
    for(int i = accountHolderName.length(); i < 20; i++){
      accountHolderName += ' ';
    }
    string appendToTransaction = "06_"+accountHolderName+"_"+accountNumber+"_"+string("00000.00_");
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
