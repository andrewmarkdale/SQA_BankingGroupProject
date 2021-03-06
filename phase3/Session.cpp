#include "Session.h"
#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;
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
    cout << "enter account holder name:\n";
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
    if(word[1] == accountHolderName){
      reader.close();
      return true;
    }
  }
  cout << "account not found\n";
  reader.close();
  return false;
};
