/*
File name: cd_account.h
Created by: Surya Kodali
Created on: 4/17/20
Synopsis: Header file for derived class CDAccount from BankAccount.
This is a Certificate of Deposit.
*/
#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "bank_account.h"
using namespace std;

class CDAccount : public BankAccount
{
public:
    CDAccount(string &_owner, double &_interestRate);
    bool withdraw(double &amount);

protected:
    double interestRate = 0.02;
};

#endif