//
//  Transaction.cpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#include "Transaction.hpp"

Transaction::Transaction()
{
}

Transaction::Transaction(string transactionType, double amount)
{
    _transactionType = transactionType;
    _amount = amount;
}

Transaction::Transaction(string transactionType)
{
    _transactionType = transactionType;
    _amount = 0.0;
}

Transaction::Transaction(const Transaction& transaction)
{
    _transactionType = transaction._transactionType;
    _amount = transaction._amount;
}

Transaction::~Transaction(void)
{
}

string Transaction::getTransactionType()
{
    return _transactionType;
}

double Transaction::getAmount()
{
    return _amount;
}
