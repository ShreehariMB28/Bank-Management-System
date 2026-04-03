#include "../include/bank.h"

int main() {
    int choice;
    load_data();
    do{
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n2. Check Balance\n3. Deposit Money\n4. Withdraw Money\n5. Display All Accounts\n6. Delete Account\n7. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_account(); break;
            case 2: login(); break;
            case 3: deposit_money(); break;
            case 4: withdraw_money(); break;
            case 5: display_all_accounts(); break;
            case 6: delete_account(); break;
            case 7: save_exit();printf("\nThank you for using the Bank Management System.\n"); break;
            default: printf("Invalid option.\n"); break;
        }
    }while(choice!=7);
    return 0;
}