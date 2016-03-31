//
//  Transaction.hpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Transaction
{
    string _transactionType;
    double _amount;
public:
    Transaction();
    Transaction(string transactionType, double amount);
    Transaction(string transactionType);
    Transaction(const Transaction& transaction);
    ~Transaction(void);
    
    string getTransactionType();
    double getAmount();
};

#endif /* Transaction_hpp */
