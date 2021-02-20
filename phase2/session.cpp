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
  return false;
  reader.close();
};

class Transaction {
  public:            
  string transactionCode;

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
    return 0; 
} 