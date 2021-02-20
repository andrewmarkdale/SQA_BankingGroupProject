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

class Transaction {
  public:            
  string currentTransaction;
  string transactionCode;
  string validTransactions[9];
  string accountHolderName;  
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
    if(currentsession.sessionType == "standard"){
      accountHolderName = currentsession.accountHolderName;
    }else{
      accountHolderName = "";
    }
  };
  void getTransaction();
  bool validateTransaction();
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
};

void Transaction::startCurrentTransaction(){
  if(currentTransaction == validTransactions[0]){
    logout();
  }
}


bool Transaction::logout(){
  ofstream writeTransactionFile("sessiontransactions.txt");
  for(int i = accountHolderName.length(); i < 20; i++){
    accountHolderName += ' ';
  }
  string appendToTransaction = string("00_")+string(accountHolderName)+string("_00000_")+string("00000.00_");
  writeTransactionFile << appendToTransaction;
  writeTransactionFile.close();
  return true;
};


class User {
  public:            
  string accountHoldername;
  float accountBalance;
  string accountNumber;
  char accountStatus;
};


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
      newTransaction.startCurrentTransaction();
    }else{
      exit(0);
    }
    return 0; 
}