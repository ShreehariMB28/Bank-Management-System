#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the blueprint for a bank account
struct Account {
    int account_number;
    char username[50];
    char password[50];
    int balance;
};

// Declare the functions you will write later
void create_account();
void login();
void deposite_balance(char acc_num[], int amount);
void verify_balance();
#endif