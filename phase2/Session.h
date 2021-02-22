#include<iostream>
#include <string>
#include <stdlib.h>
#include <fstream>


#ifndef SESSION
#define SESSION


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
#endif
