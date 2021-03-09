#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>


#ifndef SESSION
#define SESSION
/*
Session class will be used to begin a session as standard or admin, it will then
be used as a parameter for the Transaction class to begin accepting transactions.

 Passed into Transaction to facilitate all transactions. Allows transaction
 to see sessionType among other things which further allows proper writeTransactionFile
 priting etc.  

*/
using namespace std;
class Session {
  public:
    string sessionType;
    string transaction;
    string accountHolderName;
    string currentBankAccountFile;
    string sessionTransactionFile;

    Session(string CBAF, string STF){
      currentBankAccountFile = CBAF;
      sessionTransactionFile = STF;
      accountHolderExist = false;
    };

    bool accountHolderExist;
    void login();
    void getsessionType();
    bool validateAccountHolder();
};
#endif
