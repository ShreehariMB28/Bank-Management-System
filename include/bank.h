/**
 * @file bank.h
 * @brief Header file for the Bank Management System.
 *
 * Contains structure definitions for Account and Node (linked list),
 * as well as function declarations for all banking operations.
 */

#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Account
 * @brief Represents a single bank account.
 *
 * Stores the account holder's credentials (username/password),
 * a unique account number, and the current balance.
 */
struct Account {
    int account_number;   /* Unique identifier for the account */
    char username[50];    /* Account holder's username (login credential) */
    char password[50];    /* Account holder's password (login credential) */
    int balance;          /* Current balance in Rupees */
};

/**
 * @struct Node
 * @brief A singly-linked list node that wraps an Account.
 *
 * The entire bank database is stored in-memory as a singly-linked list
 * of Node structs, each containing one Account and a pointer to the
 * next node.
 */
struct Node {
    struct Account data;  /* The account data stored in this node */
    struct Node* next;    /* Pointer to the next node in the list (NULL if last) */
};

/* ==================== Function Declarations ==================== */

/**
 * @brief Creates a new bank account and appends it to the linked list.
 *
 * Prompts the user for an account number, username, and password.
 * Validates that the account number is unique before creating the account.
 * The initial balance is set to 0.
 */
void create_account();

/**
 * @brief Authenticates a user and displays their current balance.
 *
 * Prompts for username and password, then searches the linked list
 * for a matching account. Prints the balance on success, or an
 * error message on failure.
 */
void login();

/**
 * @brief Deletes a bank account after verifying credentials.
 *
 * Authenticates the user, then removes the matching node from the
 * linked list and frees its memory.
 */
void delete_account();

/**
 * @brief Loads account data from the binary file "bank_data.dat" into memory.
 *
 * Reads Account structs from disk and reconstructs the in-memory
 * linked list. Called once at program startup. If the file does not
 * exist, the program starts with an empty database.
 */
void load_data();

/**
 * @brief Saves all account data to disk and exits the program.
 *
 * Writes every Account struct from the linked list to "bank_data.dat",
 * frees all allocated memory, and terminates the program with exit(0).
 */
void save_exit();

/**
 * @brief Sorts the linked list in ascending order of balance using merge sort.
 *
 * @param headRef  Pointer to the head pointer of the linked list. Updated
 *                 in-place to point to the new head after sorting.
 */
void merge_sort(struct Node** headRef);

/**
 * @brief Splits a linked list into two roughly equal halves.
 *
 * Uses the fast/slow pointer technique (tortoise and hare) to find the
 * midpoint, then breaks the list into two separate lists.
 *
 * @param source    The head of the list to split.
 * @param frontRef  Output — pointer to the front half.
 * @param backRef   Output — pointer to the back half.
 */
void split_list(struct Node* source, struct Node** frontRef, struct Node** backRef);

/**
 * @brief Merges two sorted linked lists into a single sorted list.
 *
 * @param a  Head of the first sorted list.
 * @param b  Head of the second sorted list.
 * @return   Head of the merged sorted list.
 */
struct Node* sorted_merge(struct Node* a, struct Node* b);

/**
 * @brief Deposits money into an account after verifying credentials.
 *
 * Authenticates the user, then adds the specified amount to their balance.
 */
void deposit_money();

/**
 * @brief Withdraws money from an account after verifying credentials.
 *
 * Authenticates the user, checks for sufficient funds, and then
 * subtracts the specified amount from their balance.
 */
void withdraw_money();

/**
 * @brief Displays all accounts sorted by balance in ascending order.
 *
 * Calls merge_sort() to sort the list first, then traverses and
 * prints every account's number, username, and balance.
 */
void display_all_accounts();

#endif