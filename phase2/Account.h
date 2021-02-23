#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>


#ifndef ACCOUNT
#define ACCOUNT
/*

Account class will be used to store the information read in from 
the current bank accounts file for a transaction. This class is not 
implemented yet, so the account information is currently stored in 
transaction class.

*/
using namespace std;
class Account {
  public:
    string accountHolderName;
    float accountBalance;
    string accountNumber;
    bool accountStatus;
};
#endif
