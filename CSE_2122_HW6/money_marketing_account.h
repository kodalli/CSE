/*
File name: money_marketing_account.h
Created by: Surya Kodali
Created on: 4/17/20
Synopsis: Header file for derived class MoneyMarketAccount from BankAccount.
*/
#ifndef MONEYMARKETACCOUNT_H
#define MONEYMARKETACCOUNT_H

#include "bank_account.h"
using namespace std;

class MoneyMarketingAccount : public BankAccount
{
public:
    MoneyMarketingAccount(string &_owner);
    bool withdraw(double &amount);

protected:
    int numWithdraw = 0;
};

#endif