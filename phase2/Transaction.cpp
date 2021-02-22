#include "Transaction.h"
#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;
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
/*

Method validatePayee
terminal prompts user to input string of payee
user inputs string of payee

if payee is a valid payee the method returns true


*/

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
