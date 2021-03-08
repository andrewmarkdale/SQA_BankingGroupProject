#include "Transaction.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;
/*
is_number checks if input string is in fact a number -- if not
it returns false.
*/
bool is_number(const string& s){
     return !s.empty() && std::find_if(s.begin(),
         s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    return true;
}
/*
  getTransaction will read in the transaction type as std input and
  save it to the currentTransaction variable and then validate the transaction

  terminal will output enter transaction type
  user enters transaction type

  return type none
*/

void Transaction::getTransaction(){
  cout << "enter transaction type:\n";
  cin >> currentTransaction;
  validateTransaction();
};

bool Transaction::cancelCheck(string &input){
  if(input == "cancel"){
    cout << "transaction cancelled\n";
    return true;
  }
  return false;
}

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

/*

validatePlan takes input and will validate whether or not the input from the
user matches the allowed plans in the validPlans list. List can be quickly
altered to allow new plans to be added.

if valid plan type is entered
return true

if invalid plan type is entered
output "unknown plan"
start validate plan again. ****


**** This will be altered, our tests are off: If plan is invalid should output
invalid input and return to getTransaction.

*/

bool Transaction::validatePlan(){
  cout << "enter account type (SP - student, NP - standard):\n";
  cin >> planType;
  if(cancelCheck(planType)){return false;};
  for(int i = 0; i < 2; i++){
    if(planType == validPlans[i]){
      return true;
    }
  }
  cout << "invalid input\n";
  
  return false;
};
/*

validatePlan takes input and will validate whether or not the input from the
user matches the allowed payees in the validPayees list. List can be quickly
altered to allow new companies to be added.

Method validatePayee
terminal prompts user to input string of payee
user inputs string of payee

if payee is a valid payee the method
return true

if payee is invalid
return false


*/

bool Transaction::validatePayee(){
  cout << "enter the payee:\n";
  cin >> currentPayee;
  if(cancelCheck(currentPayee)){return false;};
  for(int i = 0; i < 3; i++){
    if(currentPayee == validPayees[i]){
      return true;
    }
  }
  cout << "invalid input\n";
  return false;
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

bool Transaction::validateAccountHolder() {
  string line;
  string checkname;
  string balance;
  ifstream reader(currentBankAccountFile);
  while (getline (reader, line)) {
    string word[4];
    checkname = "";
    balance = "";
    int counter = 0;
    for(int i = 6; i < 26; i++){
    //  if(line[i] == '_'){
    //    counter++;
    //  }else if(line[i] == ' '){
    //    counter++;
    //  }
    //  else{
    //    word[counter] += line[i];
    //  }
    if(line[i] != ' '){
      checkname += line[i];
    }
    }
    for(int i = 29; i<37;i++){
      balance += line[i];
    }

    if(checkname == accountHolderName){
      reader.close();
      accountHolderBalance = balance;
      return true;
    }
  }
  cout << "account not found\n";
  reader.close();
  return false;
};

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
  string accountNumberRead;
  string accountName;
  string balance;
  string status; 
  ifstream reader(currentBankAccountFile);
  while (getline (reader, line)) {
    accountNumberRead = "";
    accountName = "";
    balance = "";
    status ="";
    for(int i = 0; i < 5; i++){
      
      accountNumberRead += line[i];
      
    }
    for(int i = 6; i < 25; i++){
      if(line[i] != ' '){
        accountName += line[i];
      }
    }
    for(int i = 29; i<37;i++){
      balance += line[i];
    }
    status = line[27];
    if(currentTransaction == "transfer" && accountNumberTo == accountNumberRead){
      accountHolderNameTo = accountName;
      accountHolderBalanceTo = balance;
      if(status == "D"){cout << "account disabled\n"; return false;}
      return true;
    }
    if(accountName == accountHolderName && accountNumberRead == accountNumber && accountNumberTo ==""){
      accountHolderBalance = balance;
      if(status == "D"){cout << "account disabled\n"; return false;}
      return true;
    }
  }

  cout << "account number not found\n";

  reader.close();
  return false;
}


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
};

bool Transaction::checkAccountNumber(string temp_num){
  string line;
  ifstream reader(currentBankAccountFile);
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

    if(word[0] != temp_num){
      return true;
    }
    else{
      cout << "account number already created\n";
    }
  }

  reader.close();
  return false;
};
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

  if(sessiontype == "admin"){
    cout << "enter account holder name(from):\n";
    cin >> accountHolderName;
    if(cancelCheck(accountHolderName)){return false;};
    if(validateAccountHolder() == false){
      accountHolderName = "";
      return false;
    }
  }
  cout << "enter account number(from):\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){
    cout <<"enter account number(to):\n";
    cin >> accountNumberTo;
    if(cancelCheck(accountNumberTo)){accountNumberTo ="";accountHolderNameTo =""; return false;};
    if(validateAccountNumber()){
      cout <<"enter total transfer amount:\n";
      cin >> transferamount;
      if(cancelCheck(transferamount)){accountNumberTo =""; accountHolderNameTo ="";return false;};
      if(!is_number(transferamount)){cout << "invalid input\n"; accountNumberTo =""; accountHolderNameTo ="";return false;}
      if(stoi(transferamount) > stoi(accountHolderBalance)){cout << "invalid input\n"; accountNumberTo =""; accountHolderNameTo ="";return false;}
      if(stoi(transferamount) + stoi(accountHolderBalanceTo) > 9999999){cout << "invalid input\n"; accountNumberTo =""; accountHolderNameTo ="";return false;}
      if(stoi(transferamount) > 100000 && sessiontype == "standard"){cout << "invalid input\n"; accountNumberTo =""; accountHolderNameTo ="";return false;}
      
      transferStandardSessionLimit += stoi(transferamount);
      if(transferStandardSessionLimit > 100000 && sessiontype == "standard") {
        cout << "invalid input\n";
        transferStandardSessionLimit -= stoi(transferamount);
        accountNumberTo =""; accountHolderNameTo ="";
        return false;
      }
      cout <<"transfer successful\n";

      string tempname = accountHolderName;
      for(int i = accountHolderName.length(); i<20; i++){
        tempname += ' ';
      }
      for(int i = accountHolderNameTo.length(); i<20; i++){
        accountHolderNameTo += ' ';
      }
      appendTosessionTransactionFile += "02 "+tempname+" "+accountNumber+" "+transferamount+"   \n";
      appendTosessionTransactionFile += "02 "+accountHolderNameTo+" "+accountNumberTo+" "+transferamount+"   \n";
      accountNumberTo ="";
      accountHolderNameTo ="";
      if(sessiontype == "admin"){accountHolderName = "";}
      return true;
    }else{
      if(sessiontype == "admin"){accountHolderName = "";}
      accountNumberTo ="";
      accountHolderNameTo ="";
      return false;
    }
  }
  if(sessiontype == "admin"){accountHolderName = "";}
  accountNumberTo ="";
  accountHolderNameTo ="";
  return false;
}

/*

changeplan transaction, validates account number, validates plan and writes to
transaction file

terminal prompts accountNumber;
User inputs accountNumber;
validates credentials
if false returns false

Calls validatePlan()
Doesn't particularly matter if validatePLan returns false as it is handled
within that method.


Once confirmed the terminal outputs confirmation and writes to file
depending on planType!
opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/

bool Transaction::changeplan(){
  if(sessiontype == "standard"){
    cout << "privileged transaction\n";
    return false;
  }

  cout << "enter account holder name:\n";
  cin >> accountHolderName;
  if(cancelCheck(accountHolderName)){return false;};
  if(validateAccountHolder() == false){
    accountHolderName = "";
    return false;
  }

  cout << "enter account number:\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){
    if(validatePlan()){
      string tempname = accountHolderName;
      for(int i = accountHolderName.length(); i<20; i++){
        tempname += ' ';
      }
      if(planType == "NP"){
        cout << "account updated to non-student\n";
        appendTosessionTransactionFile += "08 "+tempname+" "+accountNumber+" 00000000 NP\n";
        accountHolderName = "";
        return true;
      }
      else if(planType == "SP"){
        cout << "account updated to student\n";
        appendTosessionTransactionFile += "08 "+tempname+" "+accountNumber+" 00000000 SP\n";
        accountHolderName = "";
        return true;
      }
    }
  }
  accountHolderName = "";
  return false;
}

/*

Deposit transaction, validates account number, validates amount and writes to
transaction file

var depositAmount -> user inputs amount to deposit;

validates credentials
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
bool Transaction::deposit(){
    if(sessiontype == "admin"){
    cout << "enter account holder name:\n";
    cin >> accountHolderName;
    if(cancelCheck(accountHolderName)){return false;};
    if(validateAccountHolder() == false){
      accountHolderName = "";
      return false;
    }
  }
  string depositAmount;
  cout << "enter account number:\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){
    cout << "enter deposit amount:\n";
    cin >> depositAmount;
    if(cancelCheck(depositAmount)){return false;};
    if(!is_number(depositAmount)){cout << "invalid input\n";return false;}
    if(stoi(depositAmount) > 100000){cout << "invalid input\n"; return false;}
    if(stoll(depositAmount) + stoll(accountHolderBalance) > 99999){cout << "invalid input\n"; return false;}
    cout << "deposit successful\n";

    string tempname = accountHolderName;
    for(int i = accountHolderName.length(); i<20; i++){
      tempname += ' ';
    }
    appendTosessionTransactionFile += "04 "+tempname+" "+accountNumber+" "+depositAmount+"   \n";

    if(sessiontype == "admin"){accountHolderName = "";}
    return true;
  }
  if(sessiontype == "admin"){accountHolderName = "";}
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
  if(sessiontype == "admin"){
    cout << "enter account holder name:\n";
    cin >> accountHolderName;
    if(cancelCheck(accountHolderName)){return false;};
    if(validateAccountHolder() == false){
      accountHolderName = "";
      return false;
    }
  }

  string paymentAmount;
  cout << "enter account number:\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){
    if(validatePayee()){
      cout << "enter the amount:\n";
      cin >> paymentAmount;
      if(cancelCheck(paymentAmount)){return false;};
      if(stoi(paymentAmount) > stoi(accountHolderBalance)){cout << "invalid input\n";return false;};
      if(stoi(paymentAmount) > 2000 && sessiontype == "standard"){cout << "invalid input\n";return false;};
      cout << "payment successful\n";

      string tempname = accountHolderName;
      for(int i = accountHolderName.length(); i<20;i++){
        tempname += ' ';
      }
      appendTosessionTransactionFile += "03 "+tempname+" "+accountNumber+" "+paymentAmount+"   \n";
      if(sessiontype == "admin"){accountHolderName = "";}
      return true;
    }
    if(sessiontype == "admin"){accountHolderName = "";}
    return false;
  }
  if(sessiontype == "admin"){accountHolderName = "";}
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

  if(sessiontype == "admin"){
    cout << "enter account holder name:\n";
    cin >> accountHolderName;
    if(cancelCheck(accountHolderName)){return false;};
    if(validateAccountHolder() == false){
      accountHolderName = "";
      return false;
    }
  }

  string withdrawalamount;
  cout << "enter account number:\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){
    cout << "enter withdrawal amount:\n";
    cin >> withdrawalamount;
    if(cancelCheck(withdrawalamount)){return false;};
    if(!is_number(withdrawalamount)){cout << "invalid input\n";return false;}
    if(stoi(withdrawalamount) > 50000 && sessiontype == "standard"){cout << "invalid input\n"; return false;}
    if(stoi(withdrawalamount) > stoi(accountHolderBalance)){cout << "invalid input\n";return false;}
    withdrawalStandardSessionLimit += stoi(withdrawalamount);
    if( withdrawalStandardSessionLimit > 50000 && sessiontype == "standard") {cout << "invalid input\n";  withdrawalStandardSessionLimit -= stoi(withdrawalamount); return false;}
    cout << "withdrawal successful\n";

    string tempname = accountHolderName;
    for(int i = accountHolderName.length(); i < 20; i++){
      tempname += ' ';
    }
    appendTosessionTransactionFile += "01 "+tempname+" "+accountNumber+" "+withdrawalamount+"   \n";
    if(sessiontype == "admin"){accountHolderName = "";}
    return true;
  }
  if(sessiontype == "admin"){accountHolderName = "";}
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
  ofstream writeTransactionFile(sessionTransactionFile);
  // This tempname isn't strictly necessary but I figured for consistency
  // may as well add it.
  if(sessiontype == "admin"){accountHolderName = "";};
  string tempname = accountHolderName;
  for(int i = accountHolderName.length(); i < 20; i++){
    tempname += ' ';
  }
  appendTosessionTransactionFile += string("00 ")+tempname+string(" 00000 ")+string("00000000   ");
  writeTransactionFile << appendTosessionTransactionFile;
  writeTransactionFile.close();
  cout << "session terminated";
  return true;
};

/*
disable transaction, validates session type and writes to transaction file
after user has input the confirmation character

var d -> user inputs disable confirmation

currently allows all session types
to use disable()

validates credentials
if false returns false

terminal prompts account name
user enters account name
terminal prompts account number
user enters account number
terminal prompts confirmation
user enters confirmation

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/


bool Transaction::disable(){
  if(sessiontype == "standard"){
    cout << "privileged transaction\n";
    return false;
  }

  cout << "enter account holder name:\n";
  cin >> accountHolderName;
  if(cancelCheck(accountHolderName)){return false;};
  if(validateAccountHolder() == false){
    accountHolderName = "";
    return false;
  }

  string d;
  cout << "enter account number\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){
    cout << "enter lowercase d to disable\n";
    cin >> d;
    if(cancelCheck(d)){return false;};
      if(d == "d"){
        cout << "disable successful\n";

        string tempname = accountHolderName;
        for(int i = accountHolderName.length(); i < 20; i++){
          tempname += ' ';
        }
        appendTosessionTransactionFile += string("05_")+tempname+"_"+string(accountNumber)+"_"+string("00000.00_")+string("_")+string("D\n");

        accountHolderName = "";
        return true;
      }
      else{
        cout << "not lowercase d\n";
      }

  }
  accountHolderName = "";
  return false;
}
/*
Create transaction, validates session type and writes to transaction file
after user has input the account name, account number and balance

var temp_name -> user inputs new account name
var temp_num -> user inputs new account number
var balance -> user inputs new balance

currently allows all session types
to use create()

validates credentials
if false returns false

terminal prompts account name
user enters account name
terminal prompts account number
user enters account number
terminal prompts balance
user enters balance

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/

bool Transaction::create(){

  if(sessiontype == "standard"){
    cout << "privileged transaction\n";
    return false;
  }
  string temp_name;
  int temp_num;
  string accountNumber;
  string balance;
  bool check = false;

  cout << "enter account name:\n";
  cin >> temp_name;
  if(cancelCheck(temp_name)){return false;};
  if(temp_name.length() > 20){
    cout << "invalid account length\n";
    return false;
  };

  // create an unique 5 digit account number call it temp_num
  // check to see if unique 5 digit account number is in the bank account file

  temp_num = (rand() % 99999);
  accountNumber = to_string(temp_num);
  for(int i = accountNumber.length(); i < 5; i++){
    accountNumber = "0" + accountNumber;
  }
  while(check){
    if(checkAccountNumber(accountNumber)){

      for(int i = accountNumber.length(); i < 5; i++){
        accountNumber = "0" + accountNumber;
      }
      check = true;
    }
    temp_num = (rand() % 99999);
    accountNumber = to_string(temp_num);
    check = false;
  }

  cout << "enter balance:\n";
  cin >> balance;
  if(cancelCheck(balance)){return false;};
  if(balance.length()>8){
    cout << "invalid amount\n";
    return false;
  }

  for(int i = temp_name.length(); i < 20; i++){
    temp_name += ' ';
  }

  appendTosessionTransactionFile += string("07_")+string(temp_name)+"_"+string(accountNumber)+string("_")+string(balance)+"_"+string("\n");

  return true;
}
/*
Delete transaction, validates session type and writes to transaction file
after user has input the account name, account number and balance

currently allows all session types
to use Delete()

validates credentials
if false returns false

terminal prompts success message

opens transaction file
Once confirmed, writes to transaction file
closes transaction file

returns true
*/
bool Transaction::Delete(){
  if(sessiontype == "standard"){
    cout << "privileged transaction\n";
    return false;
  }

  cout << "enter account holder name:\n";
  cin >> accountHolderName;
  if(cancelCheck(accountHolderName)){return false;};
  if(validateAccountHolder() == false){
    accountHolderName = "";
    return false;
  }

  cout << "enter account number\n";
  cin >> accountNumber;
  if(cancelCheck(accountNumber)){return false;};
  if(validateAccountNumber()){

    string tempname = accountHolderName;
    for(int i = accountHolderName.length(); i < 20; i++){
      tempname += ' ';
    }
    appendTosessionTransactionFile += "06_"+tempname+"_"+accountNumber+"_"+string("00000.00_\n");

    accountHolderName = "";
    return true;
  }
  accountHolderName = "";
  return false;
}
