/**
 * @file bank.c
 * @brief Core implementation of all banking operations.
 *
 * This file implements the Bank Management System's functionality:
 *   - Account creation, authentication, deposit, withdrawal, and deletion
 *   - Persistent storage (load from / save to a binary file)
 *   - In-memory storage using a singly-linked list
 *   - Merge sort for displaying accounts sorted by balance
 */

#include "../include/bank.h"

/**
 * @brief Global head pointer for the linked list of bank accounts.
 *
 * All banking functions operate on this shared linked list.
 * Initialized to NULL (empty database) and populated by load_data()
 * at program startup.
 */
struct Node* head = NULL;

/* ==================================================================
 *                     ACCOUNT OPERATIONS
 * ================================================================== */

/**
 * @brief Creates a new bank account and appends it to the linked list.
 *
 * Steps:
 *   1. Prompt the user for an account number.
 *   2. Traverse the list to ensure the account number is unique.
 *   3. Prompt for username and password.
 *   4. Allocate a new node, initialize balance to 0, and append it
 *      to the end of the linked list.
 */
void create_account() {
    struct Account new_acc;
    struct Node* current = head;
    char input_pass[50];

    /* --- Step 1: Get and validate the account number --- */
    int acc_num;
    printf("Enter Account Number: ");
    scanf("%d", &acc_num);

    /* Check for duplicate account numbers in the existing list */
    while (current != NULL) {
        if (current->data.account_number == acc_num) {
            printf("Account number already exists. Please choose a different number.\n");
            return;  /* Abort — duplicate found */
        }
        current = current->next;
    }

    /* --- Step 2: Collect user credentials --- */
    printf("Enter Username: ");
    scanf("%s", new_acc.username);
    printf("Enter Password: ");
    scanf("%s", input_pass);
    hash_password(input_pass, new_acc.password);
    new_acc.balance = 0;           /* New accounts start with zero balance */
    new_acc.account_number = acc_num;

    /* --- Step 3: Create a new linked-list node --- */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_acc;
    new_node->next = NULL;

    /* --- Step 4: Append the node to the end of the list --- */
    if (head == NULL) {
        /* List is empty — new node becomes the head */
        head = new_node;
    } else {
        /* Traverse to the last node and attach */
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    printf("Account created successfully!\n");
}

/**
 * @brief Authenticates a user by username/password and displays their balance.
 *
 * Traverses the linked list looking for a node whose username AND password
 * both match the user's input. Prints the balance on success.
 */
void login() {
    char input_user[50], input_pass[50],hashed_pass[50];
    int found = 0;
    struct Node* current = head;

    /* Prompt for credentials */
    printf("Username: "); scanf("%s", input_user);
    printf("Password: "); scanf("%s", input_pass);
    
    hash_password(input_pass,hashed_pass );

    /* Search the list for a matching account */
    while (current != NULL) {
        if ((strcmp(current->data.username, input_user) == 0) &&
            (strcmp(current->data.password, hashed_pass) == 0)) {
            printf("Login successful! Current Balance: Rs.%d\n", current->data.balance);
            found = 1;
            break;  /* Match found — stop searching */
        }
        current = current->next;
    }

    if (!found)
        printf("Invalid credentials.\n");
}

/**
 * @brief Deposits money into an account after credential verification.
 *
 * Flow:
 *   1. Authenticate the user (username + password).
 *   2. Prompt for the deposit amount.
 *   3. Add the amount to the account's balance.
 */
void deposit_money() {
    struct Node* current = head;
    int found = 0;
    int amount;
    char input_pass[50], input_user[50],hashed_pass[50];

    /* Prompt for credentials */
    printf("Enter Username: ");
    scanf("%s", input_user);
    printf("Enter Password: ");
    scanf("%s", input_pass);

    hash_password(input_pass,hashed_pass );

    /* Search for the matching account */
    while (current != NULL) {
        if (strcmp(current->data.username, input_user) == 0 &&
            strcmp(current->data.password, hashed_pass) == 0) {
            printf("User Verified\n");
            found = 1;

            /* Accept deposit amount and update balance */
            printf("Enter the amount you want to Deposit\n");
            scanf("%d", &amount);
            current->data.balance += amount;
            printf("Deposit successful! The new balance is: Rs.%d\n", current->data.balance);
            return;  /* Done — exit early */
        }
        current = current->next;
    }

    /* No matching account was found */
    printf("Account Not Found\n");
}

/**
 * @brief Withdraws money from an account after credential verification.
 *
 * Flow:
 *   1. Authenticate the user (username + password).
 *   2. Prompt for the withdrawal amount.
 *   3. Check that the balance is sufficient.
 *   4. Subtract the amount from the account's balance.
 */
void withdraw_money() {
    struct Node* current = head;
    int found = 0;
    int amount;
    char input_pass[50], input_user[50],hashed_pass[50];

    /* Prompt for credentials */
    printf("Enter Username: ");
    scanf("%s", input_user);
    printf("Enter Password: ");
    scanf("%s", input_pass);

    hash_password(input_pass,hashed_pass );

    /* Search for the matching account */
    while (current != NULL) {
        if (strcmp(current->data.username, input_user) == 0 &&
            strcmp(current->data.password, hashed_pass) == 0) {
            printf("User Verified\n");
            found = 1;

            /* Accept withdrawal amount */
            printf("Enter the amount you want to Withdraw\n");
            scanf("%d", &amount);

            /* Guard: ensure sufficient funds before withdrawing */
            if (amount > current->data.balance) {
                printf("Balance is less than the amount asked to Withdraw\n");
                return;
            }

            /* Deduct the amount and display updated balance */
            current->data.balance -= amount;
            printf("Withdrawal successful! The new balance is: Rs.%d\n", current->data.balance);
            return;  /* Done — exit early */
        }
        current = current->next;
    }

    /* No matching account was found */
    printf("Account Not Found\n");
}

/**
 * @brief Deletes an account from the linked list after credential verification.
 *
 * Handles two cases:
 *   - Deleting the head node  → update the head pointer.
 *   - Deleting a middle/tail node → bypass it via the previous node's next pointer.
 * Frees the memory of the removed node.
 */
void delete_account() {
    char input_user[50], input_pass[50],hashed_pass[50];
    int found = 0;
    struct Node* current = head;
    struct Node* prev = head;  /* Trails one step behind 'current' */

    /* Prompt for credentials */
    printf("Username: "); scanf("%s", input_user);
    printf("Password: "); scanf("%s", input_pass);

    hash_password(input_pass,hashed_pass );
    /* Traverse the list looking for a matching account */
    while (current != NULL) {
        if ((strcmp(current->data.username, input_user) == 0) &&
            (strcmp(current->data.password, hashed_pass) == 0)) {
            printf("Account Found and Deleted\n");
            found = 1;

            if (current == head) {
                /* Special case: removing the head node */
                head = current->next;
            } else {
                /* General case: unlink 'current' from the chain */
                prev->next = current->next;
            }

            free(current);  /* Release the node's memory */
            break;           /* Account removed — stop searching */
        }
        prev = current;          /* Advance the trailing pointer */
        current = current->next; /* Advance to the next node */
    }

    if (!found)
        printf("Invalid credentials.\n");
}

/* ==================================================================
 *                   DATA PERSISTENCE (FILE I/O)
 * ================================================================== */

/**
 * @brief Loads account data from the binary file "bank_data.dat" into memory.
 *
 * Reads Account structs one at a time from the file and builds the
 * in-memory linked list. Uses a 'tail' pointer for O(1) appends so
 * accounts are loaded in their original order.
 *
 * Called once at program startup. If the file does not exist the
 * function silently returns, leaving the list empty.
 */
void load_data() {
    FILE *file = fopen("bank_data.dat", "rb");

    /* If the file doesn't exist yet, start with an empty database */
    if (file == NULL) {
        return;
    }

    struct Account temp_acc;
    struct Node* tail = NULL;  /* Keeps track of the last node for O(1) appends */

    /*
     * Read one Account struct at a time.
     * fread returns the number of items successfully read — checking for
     * exactly 1 avoids processing partial/garbage data at EOF.
     */
    while (fread(&temp_acc, sizeof(struct Account), 1, file) == 1) {

        /* 1. Allocate memory for a new linked-list node */
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

        if (new_node == NULL) {
            printf("Memory allocation failed!\n");
            break;  /* Stop loading if out of memory */
        }

        /* 2. Copy the Account data into the new node */
        new_node->data = temp_acc;
        new_node->next = NULL;

        /* 3. Attach the new node to the end of the linked list */
        if (head == NULL) {
            head = new_node;   /* First node — becomes the head */
        } else {
            tail->next = new_node;  /* Append after the current tail */
        }

        tail = new_node;  /* Update the tail pointer */
    }

    fclose(file);
    printf("Database successfully loaded into memory!\n");
}

/**
 * @brief Saves all accounts to "bank_data.dat", frees memory, and exits.
 *
 * Traverses the entire linked list, writing each Account struct to the
 * binary file. Each node is freed immediately after its data is written,
 * ensuring no memory leaks. The program then terminates via exit(0).
 */
void save_exit() {
    FILE *file = fopen("bank_data.dat", "wb");

    if (file == NULL) {
        printf("Error: Could not save database!\n");
        exit(1);  /* Fatal error — cannot persist data */
    }

    struct Node* current = head;
    struct Node* next_node;

    /* Write each account to disk and free its node */
    while (current != NULL) {
        fwrite(&(current->data), sizeof(struct Account), 1, file);

        next_node = current->next;
        free(current);       /* Free the node's memory */
        current = next_node; /* Advance to the next node */
    }

    fclose(file);
    printf("\nAll data successfully saved to disk. Thank you for using the Bank Management System!\n");
    exit(0);
}

/* ==================================================================
 *                MERGE SORT (for linked list)
 * ================================================================== */

/**
 * @brief Merges two individually sorted linked lists into one sorted list.
 *
 * Recursively picks the smaller head node from lists 'a' and 'b',
 * building a single list sorted in ascending order of balance.
 *
 * @param a  Head of the first sorted sub-list.
 * @param b  Head of the second sorted sub-list.
 * @return   Head of the merged, fully sorted list.
 */
struct Node* sorted_merge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;

    /* Base cases: if one list is exhausted, return the other */
    if (a == NULL) return b;
    else if (b == NULL) return a;

    /* Pick the node with the smaller balance and recurse */
    if (a->data.balance <= b->data.balance) {
        result = a;
        result->next = sorted_merge(a->next, b);
    } else {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}

/**
 * @brief Splits a linked list into two halves using the fast/slow pointer technique.
 *
 * The "tortoise and hare" algorithm: 'slow' advances one step at a time
 * while 'fast' advances two steps. When 'fast' reaches the end, 'slow'
 * is at the midpoint, allowing us to split the list in two.
 *
 * @param source    Head of the list to split.
 * @param frontRef  Output — will point to the first half.
 * @param backRef   Output — will point to the second half.
 */
void split_list(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* fast;
    struct Node* slow;

    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes and 'slow' one node each iteration */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is now at the midpoint — split the list here */
    *frontRef = source;        /* Front half starts at the original head */
    *backRef = slow->next;     /* Back half starts just past the midpoint */
    slow->next = NULL;         /* Sever the link to create two separate lists */
}

/**
 * @brief Recursively sorts the linked list by balance using merge sort.
 *
 * Algorithm:
 *   1. Base case — a list of length 0 or 1 is already sorted.
 *   2. Split the list into two halves.
 *   3. Recursively sort each half.
 *   4. Merge the two sorted halves back together.
 *
 * @param headRef  Pointer to the head pointer — updated in-place to
 *                 reflect the new sorted order.
 */
void merge_sort(struct Node** headRef) {
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;

    /* Base case: 0 or 1 elements — already sorted */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    /* Split the list into two halves: 'a' and 'b' */
    split_list(head, &a, &b);

    /* Recursively sort each half */
    merge_sort(&a);
    merge_sort(&b);

    /* Merge the two sorted halves and update the head pointer */
    *headRef = sorted_merge(a, b);
}

/* ==================================================================
 *                       DISPLAY / REPORTING
 * ================================================================== */

/**
 * @brief Displays all accounts sorted by balance in ascending order.
 *
 * First sorts the linked list using merge sort, then traverses and
 * prints each account's number, username, and balance.
 */
void display_all_accounts() {
    if (head == NULL) {
        printf("No accounts found in the bank.\n");
        return;
    }

    /* Sort accounts by balance before displaying */
    merge_sort(&head);

    struct Node* current = head;
    printf("\n--- All Bank Accounts (Sorted by Balance) ---\n");
    while (current != NULL) {
        printf("Account: %d | User: %s | Balance: Rs.%d\n",
               current->data.account_number, current->data.username, current->data.balance);
        current = current->next;
    }
    printf("---------------------------------------------\n");
}

void hash_password(const char* password, char* output) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    sprintf(output, "%lx", hash);  // store as hex string
}










