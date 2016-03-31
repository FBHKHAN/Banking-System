//
//  Account.cpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#include "Account.hpp"
#include "Transaction.hpp"

Account::Account(void)
{
    transactionCount = 0;
    capacity = 101;
    transactions = new Transaction[capacity];
}

Account::~Account(void)
{
    delete[] transactions;
}

Account::Account(Depositor& depositor, double balance, int accountNumber, string accountType, int status)
{
    _depositor = depositor;
    _balance = balance;
    _accountNumber = accountNumber;
    _accountType = accountType;
    _status = status;
    
    transactionCount = 0;
    capacity = 101;
    transactions = new Transaction[capacity];
}
Account::Account(const Account& account)
{
    _depositor = account._depositor;
    _balance = account._balance;
    _accountNumber = account._accountNumber;
    _accountType = account._accountType;
    _status = account._status;
    
    capacity = account.capacity;
    transactionCount = account.transactionCount;
    
    transactions = new Transaction[capacity];
    for(int i=0; i<transactionCount; i++)
    {
        transactions[i] = account.transactions[i];
    }
}

void Account::addTransaction(Transaction transaction)
{
    if (transactionCount>=capacity-1)
    {
        capacity = capacity * 2;
        Transaction* newTransaction = new Transaction[capacity];
        for(int i=0; i<transactionCount; i++)
            newTransaction[i] = transactions[i];
        
        delete[] transactions;
        transactions = newTransaction;
    }
    transactions[transactionCount] = transaction;
    transactionCount++;
}

int Account::getTransactionCount()
{
    return transactionCount;
}

Transaction Account::getTransaction(int index)
{
    return transactions[index];
}

double Account::getBalance()
{
    return _balance;
}
Depositor& Account::getDepositor()
{
    return _depositor;
}
int Account::getAccountNumber()
{
    return _accountNumber;
}
string Account::getAccountType()
{
    return _accountType;
}
void Account::makeDeposit(double amount)
{
    addTransaction(Transaction("deposit", amount));
    _balance += amount;
}
bool Account::makeWithdrawal(double amount)
{
    if (amount>_balance)
    {
        return false;
    }
    else
    {
        addTransaction(Transaction("withdraw", amount));
        _balance -= amount;
        return true;
    }
}

void Account::open()
{
    addTransaction(Transaction("open"));
    _status = 1;
}
void Account::close()
{
    addTransaction(Transaction("close"));
    _status = 0;
}

bool Account::isClosed()
{
    return _status==0;
}