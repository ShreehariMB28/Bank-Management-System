#include "../include/bank.h"
struct Node* head = NULL;

void create_account() {
    struct Account new_acc;
    struct Node* current = head;
    char input_user[50], input_pass[50];

    int acc_num;
    printf("Enter Account Number: ");
    scanf("%d", &acc_num);
    while (current != NULL) {
        if (current->data.account_number == acc_num) {
            printf("Account number already exists. Please choose a different number.\n");
            return; // Exit the function to prevent account creation
        }
        current = current->next;
    }
    printf("Enter Username: ");
    scanf("%s", new_acc.username);
    printf("Enter Password: ");
    scanf("%s", new_acc.password);
    new_acc.balance = 0;
    new_acc.account_number = acc_num;

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_acc;
    new_node->next = NULL;
    if (head == NULL) {
        head = new_node;
    } else {
        current = head;
    while (current->next != NULL) {
         current = current->next;
    }
    
    current->next = new_node;}

    printf("Account created successfully!\n");
}

void login() {
    
    char input_user[50], input_pass[50];
    int found = 0;
    struct Node* current = head;
    
    printf("Username: "); scanf("%s", input_user);
    printf("Password: "); scanf("%s", input_pass);

    while (current != NULL) {
        if ((strcmp(current->data.username, input_user) == 0) && (strcmp(current->data.password, input_pass) == 0)) {
            printf("Login successful! Current Balance: Rs.%d\n", current->data.balance);
            found = 1;
            break; // Stop searching once found
        }
        current = current->next; 
    }
    
    if (!found) printf("Invalid credentials.\n");
}
void deposit_money(){
    struct Node* current = head; 
    int found = 0;
    int amount;
    char input_pass[50],input_user[50];
    printf("Enter Username: ");
    scanf("%s", input_user);
    printf("Enter Password: ");
    scanf("%s", input_pass);
    while (current!= NULL) {
        if (strcmp(current->data.username, input_user) == 0 && strcmp(current->data.password, input_pass) == 0) {
            printf("User Verified\n");
            found = 1;
            
            printf("Enter the amount you want to Deposit\n");
            scanf("%d",&amount);
            current->data.balance += amount; 
            printf("Deposit successful! The new balance is: Rs.%d\n", current->data.balance);
            return; 
        }
        current = current->next; 
    }
     printf("Account Not Found\n");
    
    }  
void withdraw_money(){
    struct Node* current = head; 
    int found = 0;
    int amount;
    char input_pass[50],input_user[50];
    printf("Enter Username: ");
    scanf("%s", input_user);
    printf("Enter Password: ");
    scanf("%s", input_pass);
    while (current!= NULL) {
        if (strcmp(current->data.username, input_user) == 0 && strcmp(current->data.password, input_pass) == 0) {
            printf("User Verified\n");
            found = 1;
            
            printf("Enter the amount you want to Withdraw\n");
            scanf("%d",&amount);
            if(amount > current->data.balance){
                printf("Balance is less than the amount asked to Withdraw\n");
                return;
            }
            current->data.balance -= amount; 
            printf("Deposit successful! The new balance is: Rs.%d\n", current->data.balance);
            return; 
        }
        current = current->next; 
    }
     printf("Account Not Found\n");
    
    }  

void load_data() {
    FILE *file = fopen("bank_data.dat", "rb");
    
    // If the file doesn't exist yet, just return and start with an empty list
    if (file == NULL) {
        return; 
    }

    struct Account temp_acc;
    struct Node* tail = NULL; // Keeps track of the last node for fast insertions

    // Read exactly one Account struct at a time. 
    // This is the safest way to read binary files in C to avoid reading garbage data at the end of a file.
    while (fread(&temp_acc, sizeof(struct Account), 1, file) == 1) {
        
        // 1. Allocate memory on the heap for the new node
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        
        if (new_node == NULL) {
            printf("Memory allocation failed!\n");
            break;
        }

        // 2. Copy the data we just read from the file into the new node
        new_node->data = temp_acc;
        new_node->next = NULL;

        // 3. Attach the node to our Linked List
        if (head == NULL) {
            // If the list is empty, this new node becomes the head
            head = new_node; 
        } else {
            // Otherwise, attach it to the end of the list
            tail->next = new_node; 
        }
        
        // Update the tail to be this new last node
        tail = new_node; 
    }

    fclose(file);
    printf("Database successfully loaded into memory!\n");
}

// 1. The Merge Function (Translates your 'merge' function)
// This stitches the two halves back together in sorted order.
struct Node* sorted_merge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;

    // Base cases: if one list is empty, return the other
    if (a == NULL) return b;
    else if (b == NULL) return a;

    // Pick either 'a' or 'b', and recur. We are sorting by balance here.
    if (a->data.balance <= b->data.balance) {
        result = a;
        result->next = sorted_merge(a->next, b);
    } else {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}

// 2. The Split Function (Translates finding the 'mid' index)
// Uses the fast/slow pointer strategy to cut the list in half.
void split_list(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* fast;
    struct Node* slow;
    
    slow = source;
    fast = source->next;

    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast!= NULL) {
        fast = fast->next;
        if (fast!= NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is now at the midpoint. 
    *frontRef = source;
    *backRef = slow->next;
    
    // Break the list in two by setting the midpoint's next to NULL!
    slow->next = NULL; 
}

// 3. The Main Sort Function (Translates your 'mergeSort' function)
void merge_sort(struct Node** headRef) {
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    // Base case: length 0 or 1 means it's already sorted
    if ((head == NULL) ||
        (head->next == NULL)) {
        return;
    }

    // Split head into 'a' and 'b' sublists
    split_list(head, &a, &b);

    // Recursively sort the sublists
    merge_sort(&a);
    merge_sort(&b);

    // Merge the two sorted lists together and update the head pointer
    *headRef = sorted_merge(a, b);
}



void save_exit() {
    FILE *file = fopen("bank_data.dat", "wb"); 
    
    if (file == NULL) {
        printf("Error: Could not save database!\n");
        exit(1);
    }

    struct Node* current = head;
    struct Node* next_node;

    while (current!= NULL) {
        fwrite(&(current->data), sizeof(struct Account), 1, file); 
        
        next_node = current->next;
        free(current); 
        current = next_node;
    }

    fclose(file);
    printf("\nAll data successfully saved to disk. Thank you for using the Bank Management System!\n");
    exit(0);
}


void display_all_accounts(){
    if (head == NULL) {
        printf("No accounts found in the bank.\n");
        return;
    }

    // Call the sorting algorithm to sort the list by balance first
    merge_sort(&head);

    struct Node* current = head;
    printf("\n--- All Bank Accounts (Sorted by Balance) ---\n");
    while (current!= NULL) {
        printf("Account: %d | User: %s | Balance: Rs.%d\n", 
               current->data.account_number, current->data.username, current->data.balance);
        current = current->next;
    }
    printf("---------------------------------------------\n");
}



