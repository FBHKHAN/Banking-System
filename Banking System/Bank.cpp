//
//  Bank.cpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#include "Bank.hpp"

Bank::Bank(void)
{
    accountsNumber = 0;
}

Bank::~Bank(void)
{
}

int Bank::getAccounsNumber()
{
    return accountsNumber;
}

bool Bank::openAccount(string firstName, string lastName, string ssn, int accountNumber, string accountType, double balance)
{
    if (addAccount(firstName, lastName, ssn, accountNumber, accountType, balance, 1))
    {
        int index = findAccount(accountNumber);
        if (index>=0)
        {
            _accounts[index]->open();
        }
        return true;
    }
    return false;
}

bool Bank::addAccount(string firstName, string lastName, string ssn, int accountNumber, string accountType, double balance, int status)
{
    if (accountsNumber<MAX_NUM - 1 && findAccount(accountNumber) == -1)
    {
        Name name(firstName, lastName);
        Depositor depositor(name, ssn);
        _accounts[accountsNumber] = new Account(depositor, balance, accountNumber, accountType, status);
        accountsNumber++;
        return true;
    }
    return false;
}

int Bank::findAccount(int accountNumber)
{
    for (int i = 0; i<accountsNumber; i++)
    {
        if (_accounts[i]->getAccountNumber() == accountNumber)
            return i;
    }
    return -1;
}

int Bank::findAccountSSN(string ssn)
{
    for (int i = 0; i<accountsNumber; i++)
    {
        if (_accounts[i]->getDepositor().getSSN() == ssn)
            return i;
    }
    return -1;
}

Account* Bank::getAccount(int index)
{
    return _accounts[index];
}

bool Bank::deleteAccount(int index)
{
    if (index >= 0 && index<accountsNumber)
    {
        for (int i = index; i<accountsNumber; i++)
            _accounts[i] = _accounts[i + 1];
        
        accountsNumber--;
        return true;
    }
    else {
        return false;
    }
}
