//
//  main.cpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "Bank.hpp"

using namespace std;

/*
 This function fills up the array (up to max_accts) and
 returns the actual number of accounts read in (referred to as num_accts).
 */
int read_accts(Bank& bank, int max_accts)
{
    int i = 0;
    //ifstream infile("C:\\Users\\Smart PC\\Desktop\\Assignment 3 (3110)\\myinput.txt");
    ifstream infile("myinput");
    
    string whiteSpace;
    
    getline(infile, whiteSpace);
    
    // check is file can be opened
    if (infile)
    {
        // read only first max_accts accounts,
        // in order to avoid overflow
        for (i = 0; i<max_accts; i++)
        {
            string firstName;
            string lastName;
            string ssn;
            string accountType;
            int accountNumber;
            int status;
            double balance;
            int transactions;
            
            infile >> firstName;
            
            // check is end of file reached
            if (!infile.eof())
            {
                infile >> lastName;
                infile >> ssn;
                infile >> accountNumber;
                infile >> accountType;
                infile >> balance;
                infile >> status;
                infile >> transactions;
                
                bank.addAccount(firstName, lastName, ssn, accountNumber, accountType, balance, status);
                
                int index = bank.findAccount(accountNumber);
                Account* acc = bank.getAccount(index);
                for(int i=0; i<transactions; i++)
                {
                    string transactionType;
                    double amount;
                    
                    infile >> transactionType;
                    infile >> amount;
                    
                    if (acc)
                        acc->addTransaction(Transaction(transactionType, amount));
                }
            }
            else {
                break;
            }
        }
        infile.close();
    }
    else {
        cout << "cannot open inpout file" << endl;
    }
    
    return i;
}

/*
 This function only displays the menu.
 */
void menu()
{
    cout << "Select one of the following:" << endl << endl;
    cout << "   W - Withdrawal" << endl;
    cout << "   D - Deposit" << endl;
    cout << "   N - New account" << endl;
    cout << "   B - Balance" << endl;
    cout << "   I - Account Info" << endl;
    cout << "   H - Account Info plus Account Transaction History" << endl;
    cout << "   C - Close Account (close but do not delete the account)" << endl;
    cout << "   R - Reopen a closed account" << endl;
    cout << "   X - Delete Account (close and delete the account from the database))" << endl;
    cout << "   Q - Quit" << endl;
}

/*
 This function prompts the user for the account number. If the account does not exist,
 it prints an error message. Otherwise, it asks the user for the amount of the withdrawal.
 If the account does not contain sufficient funds, an it prints an error message and does
 not perform the transaction.
 */
void withdrawal(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        if (index >= 0)
        {
            double amount;
            
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            
            // check is there possible to withdraw
            if (amount>0)
            {
                // check is sufficient balance at account
                if (bank.getAccount(index)->makeWithdrawal(amount))
                {
                    cout << "Withdraw is completed." << endl;
                }
                else {
                    cout << "Error. Insuffucient funds." << endl;
                }
            }
            else {
                cout << "Error. Invalid amount, needed to entyer positiove number." << endl;
            }
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

/*
 This function prompts the user for the account number. If the account does not exist,
 it prints an error message. Otherwise, it asks the user for the amount of the deposit.
 */
void deposit(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        if (index >= 0)
        {
            double amount;
            
            cout << "Enter amount to deposit: ";
            cin >> amount;
            
            // check is there possible to withdraw
            if (amount>0)
            {
                bank.getAccount(index)->makeDeposit(amount);      //deposit operation
                cout << "Deposit is completed." << endl;
            }
            else {
                cout << "Error. Invalid amount, needed to entyer positiove number." << endl;
            }
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

/*
 This function prompts the user for a new account number. If the account already exists,
 it prints an error message. Otherwise, it adds the account to the database. The program
 then prompts the user to enter the new depositorís first name, last name, social security
 number, the account type (Checking, Savings, or CD), and the initial opening deposit..
 The function returns the new number of accounts in the database.
 */
void new_acct(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        if (index == -1)
        {
            double amount;
            string firstName;
            string lastName;
            string SSN;
            string accountType;
            
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            do
            {
                cout << "Enter Social Security Number: ";
                cin >> SSN;
                // SSN is 9 digits, check for validity
                if (SSN.length() == 9)
                {
                    break;
                }
                else {
                    cout << "Error. Invalid SSN, needed to enter 9 digits. Pleasy try again." << endl;
                }
            } while (true);
            
            do
            {
                cout << "Enter Account type (C - Checking, S - Saving, D - CD) : ";
                cin >> accountType;
                
                // check for validity
                if (accountType == "C" || accountType == "S" || accountType == "D")
                {
                    break;
                }
                else {
                    cout << "Error. Invalid Account type. Please try again" << endl;
                }
            } while (true);
            
            do
            {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                
                // check for validity
                if (amount>0)
                {
                    break;
                }
                else {
                    cout << "Error. Invalid amount, needed to entyer positiove number." << endl;
                }
            } while (true);
            
            if (bank.openAccount(firstName, lastName, SSN, requested_account, accountType, amount))
                cout << "Account is opened." << endl;
            else
                cout << "Error. Cannot open account." << endl;
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" already exists." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

void close_acct(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        Account* acc = bank.getAccount(index);
        
        if (index >= 0)
        {
            if (!acc->isClosed())
            {
                acc->close();
                cout << "Account number \"" << requested_account << "\" has been closed. "<< endl;
            } else {
                cout << "Error. Account number \"" << requested_account << "\" is already closed." << endl;
            }
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

void reopen_acct(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        Account* acc = bank.getAccount(index);
        
        if (index >= 0)
        {
            if (acc->isClosed())
            {
                acc->open();
                cout << "Account number \"" << requested_account << "\" has been reopened. "<< endl;
            } else {
                cout << "Error. Account number \"" << requested_account << "\" is already opened." << endl;
            }
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}


/*
 This function prompts the user for an account number. If the account does not exist,
 or if the account exists but has a non-zero balance, it prints an error message.
 Otherwise, it closes and deletes the account. It returns the new number of accounts.
 */
void delete_acct(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        if (index >= 0)
        {
            if (bank.deleteAccount(index))
                cout << "Account is closed." << endl;
            else
                cout << "Error. Cannot close account." << endl;
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

/*
 This function prompts the user for an account number. If the account does not exist,
 it prints an error message. Otherwise, it prints the account balance.
 */
void balance(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        Account* acc = bank.getAccount(index);
        if (index >= 0)
        {
            acc->addTransaction(Transaction("banance"));
            cout << "Balance is: " << fixed << setprecision(2) << acc->getBalance() << endl;
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

/*
 This function prompts the user for a social security number. If the account does not exist,
 it prints an error message. Otherwise, it prints the complete account information
 for the account requested .
 */
void account_info(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        Account* acc = bank.getAccount(index);
        
        if (index >= 0)
        {
            acc->addTransaction(Transaction("getinfo"));
            
            if (acc->getAccountType() == "S")
                cout << "Saving ";
            else if (acc->getAccountType() == "C")
                cout << "Checking ";
            else if (acc->getAccountType() == "D")
                cout << "CD ";
            
            cout << " Account #" << acc->getAccountNumber() << endl;
            cout << " Depositor info:" << endl;
            cout << "   First name: " << acc->getDepositor().getName().getFirstname() << endl;
            cout << "   Last name: " << acc->getDepositor().getName().getLastname() << endl;
            cout << "   SSN: " << acc->getDepositor().getSSN() << endl;
            cout << " Balance is: " << fixed << setprecision(2) << acc->getBalance() << endl;
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}

void account_info_tr(Bank& bank)
{
    int index, requested_account;
    
    //prompt for account number
    cout << endl << "Enter the account number: ";
    cin >> requested_account;
    
    // account #0 is not valid
    if (requested_account != 0)
    {
        index = bank.findAccount(requested_account);
        Account* acc = bank.getAccount(index);
        
        if (index >= 0)
        {
            acc->addTransaction(Transaction("getinfo_tr"));
            
            if (acc->getAccountType() == "S")
                cout << "Saving ";
            else if (acc->getAccountType() == "C")
                cout << "Checking ";
            else if (acc->getAccountType() == "D")
                cout << "CD ";
            
            cout << " Account #" << acc->getAccountNumber() << endl;
            cout << " Depositor info:" << endl;
            cout << "   First name: " << acc->getDepositor().getName().getFirstname() << endl;
            cout << "   Last name: " << acc->getDepositor().getName().getLastname() << endl;
            cout << "   SSN: " << acc->getDepositor().getSSN() << endl;
            cout << " Balance is: " << fixed << setprecision(2) << acc->getBalance() << endl;
            
            int trCount = acc->getTransactionCount();
            cout << endl << "Transaction List:  [" << trCount << " trsnsaction(s)]" << endl;
            for(int j=0; j<trCount; j++)
            {
                cout << acc->getTransaction(j).getTransactionType();
                cout << "\t";
                if (acc->getTransaction(j).getAmount()>0)
                {
                    cout << acc->getTransaction(j).getAmount();
                }
                cout << endl;
            }
        }
        else {
            cout << "Error. Account number \"" << requested_account << "\" is not found." << endl;
        }
    }
    else {
        cout << "Error. Invalid account number." << endl;
    }
}


/*
 This function prints a table of the complete account information for every active account.
 */
void print_accts(Bank& bank)
{
    ofstream outfile("myoutput.txt");
    
    if (outfile)
    {
        for (int i = 0; i < bank.getAccounsNumber(); i++)
        {
            Account* acc = bank.getAccount(i);
            
            outfile << acc->getDepositor().getName().getFirstname();
            outfile << "\t";
            outfile << acc->getDepositor().getName().getLastname();
            outfile << "\t";
            outfile << acc->getDepositor().getSSN();
            outfile << "\t";
            outfile << acc->getAccountNumber();
            outfile << "\t";
            // save as char
            outfile << acc->getAccountType();
            outfile << "\t";
            outfile << fixed << setprecision(2) << acc->getBalance();
            outfile << "\t";
            outfile << fixed << setprecision(2) << (acc->isClosed() ? 0 : 1);
            outfile << "\t";
            outfile << fixed << setprecision(2) << acc->getTransactionCount();
            outfile << endl;
            
            for(int j=0; j<acc->getTransactionCount(); j++)
            {
                Transaction tr = acc->getTransaction(j);
                outfile << tr.getTransactionType();
                outfile << "\t";
                outfile << tr.getAmount();
                outfile << endl;
            }
        }
        outfile.close();
    }
    else {
        cout << "Cannot open output file";
    }
}

int main()
{
    string choice;
    Bank bank;
    int accountsNumber = 0;
    bool stop = false;
    
    accountsNumber = read_accts(bank, MAX_NUM);
    print_accts(bank);
    
    do
    {
        cout << endl;
        menu();
        cout << "Your choice: ";
        cin >> choice;
        
        if (choice == "Q" || choice == "q")
        {
            stop = true;
        }
        else if (choice == "W" || choice == "w")
        {
            withdrawal(bank);
        }
        else if (choice == "D" || choice == "d")
        {
            deposit(bank);
        }
        else if (choice == "N" || choice == "n")
        {
            new_acct(bank);
        }
        else if (choice == "B" || choice == "b")
        {
            balance(bank);
        }
        else if (choice == "I" || choice == "i")
        {
            account_info(bank);
        }
        else if (choice == "H" || choice == "h")
        {
            account_info_tr(bank);
        }
        else if (choice == "C" || choice == "c")
        {
            close_acct(bank);
        }
        else if (choice == "R" || choice == "r")
        {
            reopen_acct(bank);
        }
        else if (choice == "X" || choice == "x")
        {
            delete_acct(bank);
        }
        else
        {
            cout << "Invalid choice, please try again." << endl;
        }
    } while (!stop);
    
    print_accts(bank);
    system("pause");
    
    return 0;
}