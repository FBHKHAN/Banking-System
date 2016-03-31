//
//  Bank.hpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#ifndef Bank_hpp
#define Bank_hpp

#include <stdio.h>

#define MAX_NUM 100

#include "Account.hpp"

class Bank
{
    Account* _accounts[MAX_NUM];
    int accountsNumber;
public:
    Bank(void);
    ~Bank(void);
    
    bool openAccount(string firstName, string lastName, string ssn, int accountNumber, string accountType, double balance);
    bool addAccount(string firstName, string lastName, string ssn, int accountNumber, string accountType, double balance, int status);
    
    int findAccount(int accountNumber);
    int findAccountSSN(string ssn);
    Account* getAccount(int index);
    bool deleteAccount(int index);
    
    int getAccounsNumber();
};

#endif /* Bank_hpp */
