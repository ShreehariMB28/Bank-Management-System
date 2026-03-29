#include "../include/bank.h"

void create_account() {
    struct Account new_acc;
    FILE *file = fopen("bank_data.dat", "ab"); // Append binary

    printf("Enter Account Number: ");
    scanf("%d", &new_acc.account_number);
    printf("Enter Username: ");
    scanf("%s", &new_acc.username);
    printf("Enter Password: ");
    scanf("%s", &new_acc.password);
    new_acc.balance = 0.0;

    fwrite(&new_acc, sizeof(struct Account), 1, file); // Write struct to file
    fclose(file);
    printf("Account created successfully!\n");
}

void login() {
    struct Account acc;
    char input_user[50], input_pass[50];
    int found = 0;
    FILE *file = fopen("bank_data.dat", "rb"); // Read binary

    if (!file) {
        printf("No database found.\n");
        return;
    }

    printf("Username: "); scanf("%s", &input_user);
    printf("Password: "); scanf("%s", &input_pass);

    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if ((strcmp(acc.username, input_user) == 0) && (strcmp(acc.password, input_pass) == 0)) {
            printf("Login successful! Current Balance: Rs.%d\n", acc.balance);
            found = 1;
            break; // Stop searching once found
        }
    }
    fclose(file);
    if (!found) printf("Invalid credentials.\n");
}
void verify_balance(){
    
    struct Account acc;
    int found = 0;
    int amount;
    char input_pass[50],input_user[50];
    printf("Enter Username: ");
    scanf("%s", input_user);
    printf("Enter Password: ");
    scanf("%s", input_pass);
    FILE *file = fopen("bank_data.dat", "rb"); // Read binary

    if (!file) {
        printf("No database found.\n");
        return;
    }
    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if ((strcmp(acc.username, input_user) == 0) && (strcmp(acc.password, input_pass) == 0)) {
            printf("Account Verified\n");
            found = 1;
            break; 
        }
    }
    
    if(found){
        printf("Enter Amount: ");
        scanf("%d", &amount);
        char acnt[50];
        sprintf(acnt, "%d", acc.account_number);
        deposite_balance(acnt, amount);
    }
    else{
        printf("Account Not Found\n");
    }  
    fclose(file);
  
}
void deposite_balance(char acc_num[], int amount){

    struct Account acc;
    char temp[50];
    int found = 0;
    FILE *file = fopen("bank_data.dat", "rb+"); 

    if (!file) {
        printf("No database found.\n");
        return;
    }
    while (fread(&acc, sizeof(struct Account), 1, file)) {
        sprintf(temp, "%d", acc.account_number);
        if ((strcmp(temp, acc_num) == 0)) {
            
            acc.balance=acc.balance+amount;
            fseek(file, -sizeof(struct Account), SEEK_CUR);

            fwrite(&acc, sizeof(struct Account), 1, file);
            printf("The new balance is : Rs.%d\n",acc.balance);
            found = 1;
            break; 
        }
    }

    fclose(file);

}




















