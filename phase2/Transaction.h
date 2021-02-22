#ifndef Transaction
#define Transaction


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