/*
File name: money_marketing_account.cpp
Created by: Surya Kodali
Created on: 4/17/20
Synopsis: Implementation file for derived class MoneyMarketAccount from BankAccount.
*/
#include "bank_account.h"
#include "money_marketing_account.h"
#include <string>
using namespace std;

// Constructor
MoneyMarketingAccount::MoneyMarketingAccount(string &_owner) : BankAccount(_owner)
{
    //empty
}
bool MoneyMarketingAccount::withdraw(double &amount)
{
    // free 2 withdraws without fee
    double fee = 1.50;
    // withdraws money from account, if amount is non positive or insufficient funds returns false
    if (numWithdraw < 2 && amount > 0 && balance - amount >= 0)
    {
        balance -= amount;
        numWithdraw++;
        return true;
    }
    else if (amount > 0 && balance - amount - fee >= 0)
    {
        balance -= amount + fee;
        return true;
    }
    else
        return false;
}