//
//  Account.hpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#ifndef Account_hpp
#define Account_hpp

#include <stdio.h>
#include "Depositor.hpp"
#include "Transaction.hpp"

class Account
{
    Depositor _depositor;
    double _balance;
    int _accountNumber;
    string _accountType;
    int _status;
    
    int capacity;
    int transactionCount;
    Transaction* transactions;
public:
    Account(void);
    Account(Depositor& depositor, double balance, int accountNumber, string accountType, int status);
    Account(const Account& account);
    ~Account(void);
    
    void addTransaction(Transaction transaction);
    int getTransactionCount();
    Transaction getTransaction(int index);
    
    void open();
    void close();
    bool isClosed();
    
    double getBalance();
    Depositor& getDepositor();
    int getAccountNumber();
    string getAccountType();
    void makeDeposit(double amount);
    bool makeWithdrawal(double amount);
};
#endif /* Account_hpp */
