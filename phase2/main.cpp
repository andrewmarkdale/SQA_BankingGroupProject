#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "Transaction.h"
#include "Session.h"

using namespace std;

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
