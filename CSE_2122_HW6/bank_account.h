/*
File name: bank_account.h
Created by: Surya Kodali
Created on: 4/17/20
Synopsis: Header file for bank_account super class for money marketing and cd accounts.
*/

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
using namespace std;

class BankAccount
{
public:
    BankAccount(string &_owner);
    bool deposit(double &amount);
    string getName();
    double getBalance();
    virtual bool withdraw(double &amount);

protected:
    string owner = "Joe Doe";
    double balance = 0.0;
};

#endif
