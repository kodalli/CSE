/*
File name: bank_account.cpp
Created by: Surya Kodali
Created on: 4/17/20
Synopsis: Implementation file for bank_account super class for money marketing and cd accounts.
*/
#include "bank_account.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor
BankAccount::BankAccount(string &_owner) : owner(_owner)
{
    // empty
}
bool BankAccount::deposit(double &amount)
{
    // depost money into bankaccount, if amount is non positive returns false
    if (amount > 0)
    {
        balance += amount;
        return true;
    }
    else
        return false;
}

bool BankAccount::withdraw(double &amount)
{
    // withdraws money from account, if amount is non positive or insufficient funds returns false
    if (amount > 0 && balance - amount >= 0)
    {
        balance -= amount;
        return true;
    }
    else
        return false;
}

string BankAccount::getName()
{
    // returns holder name
    return owner;
}

double BankAccount::getBalance()
{
    // returns holder balance
    return balance;
}
