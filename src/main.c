/**
 * @file main.c
 * @brief Entry point for the Bank Management System.
 *
 * Presents a menu-driven interface that lets the user perform
 * banking operations (create account, check balance, deposit,
 * withdraw, display accounts, delete account, and exit).
 * All account data is persisted to a binary file on disk.
 */

#include "../include/bank.h"

int main() {
    int choice;

    /* Load any previously saved accounts from "bank_data.dat" into memory */
    load_data();

    do {
        /* Display the main menu */
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Check Balance\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Display All Accounts\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        /* Route the user's choice to the appropriate handler function */
        switch (choice) {
            case 1: create_account();       break;
            case 2: login();                break;  /* Login also shows balance */
            case 3: deposit_money();        break;
            case 4: withdraw_money();       break;
            case 5: display_all_accounts(); break;
            case 6: delete_account();       break;
            case 7:
                save_exit();  /* Save data to disk and terminate the program */
                printf("\nThank you for using the Bank Management System.\n");
                break;
            default:
                printf("Invalid option. Please choose between 1 and 7.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}