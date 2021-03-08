#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "Session.h"
#ifndef TRANSACTION
#define TRANSACTION

using namespace std;


/*

Transaction class will take an instance of Session as a parameter and will
then begin accepting transactions.

Transactions consist of the following:
logout
withdrawal
deposit
transfer
paybill
disable
delete
create
changeplan

Handles all transactions.

*/

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
  string accountHolderBalance;
  string accountHolderBalanceTo;
  string sessiontype;
  string currentBankAccountFile;
  string sessionTransactionFile;
  string appendTosessionTransactionFile;
  int withdrawalStandardSessionLimit;
  int transferStandardSessionLimit;
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
    currentBankAccountFile = currentsession.currentBankAccountFile;
    sessionTransactionFile = currentsession.sessionTransactionFile;
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
  bool validateAccountHolder();
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
  bool cancelCheck(string &input);
  bool checkAccountNumber(string temp_num);
  bool validateAccountStatus();
};
#endif
