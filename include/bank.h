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
struct Node {
    struct Account data;
    struct Node* next;
};
// Declare the functions you will write later
void create_account();
void login();
void deposite_balance(int acc_num, int amount);
void verify_balance();
void load_data();
void save_exit();
void merge_sort(struct Node** headRef);
void split_list(struct Node* source, struct Node** frontRef, struct Node** backRef);
struct Node* sorted_merge(struct Node* a, struct Node* b);
void display_all_accounts();
#endif