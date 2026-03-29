#include "../include/bank.h"

int main() {
    int choice;
    do{
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n2. Login\n3. Update Balance\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create_account(); break;
            case 2: login(); break;
            case 3: verify_balance(); break;
            case 4: printf("\nThank you for using the Bank Management System.\n"); break;
            default: printf("Invalid option.\n"); break;
        }
    }while(choice!=4);
    return 0;
}