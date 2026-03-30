# Bank Management System in C

A console-based bank management application built in C using modular files, linked-list storage in memory, and binary file persistence on disk.

## Overview

This project manages bank accounts with a simple menu-driven interface. Account data is loaded from a binary file at startup, stored in a linked list during runtime, and written back to disk when exiting.

## Features

- Create new account with unique account number validation
- Login/check balance using username and password
- Verify user credentials before allowing balance update
- Deposit money into an account
- Display all accounts sorted by balance (ascending)
- Persistent storage using a binary data file (`bank_data.dat`)

## Project Structure

```text
bank-system/
|-- Makefile
|-- README.md
|-- .gitignore
|-- include/
|   `-- bank.h
|-- src/
|   |-- main.c
|   `-- bank.c
|-- bin/
`-- build/
```

## Tech Details

- Language: C
- Build tool: Make + GCC
- Data structure: Singly linked list (`struct Node`)
- Persistence: Binary file read/write with `fread` and `fwrite`

## Account Model

```c
struct Account {
    int account_number;
    char username[50];
    char password[50];
    int balance;
};
```

## Menu Options

When you run the app, the menu is:

1. Create Account
2. Check Balance
3. Update Balance
4. Display All Accounts
5. Exit

## Data File

- `bank_data.dat` is created in the project root.
- `load_data()` reads all saved accounts into memory at startup.
- `save_exit()` writes accounts to disk and frees allocated linked-list memory before exiting.

## Prerequisites

- GCC (MinGW/MSYS2 on Windows, or GCC on Linux/macOS)
- Make

## Build

From the project root:

```bash
make
```

This builds the application from:

- `src/main.c`
- `src/bank.c`

and outputs executable to `bin/`.

## Running

Manual compile command (as requested):

```bash
gcc src/main.c src/bank.c -o bin/bank_app.exe
```

Run on Windows PowerShell:

```powershell
.\bin\bank_app.exe
```

Run on Git Bash/Linux/macOS (if built without `.exe`):

```bash
./bin/bank_app
```

## Clean

```bash
make clean
```

## Notes and Limitations

- Passwords are stored as plain text (no hashing/encryption).
- Input validation is basic and assumes correct input types.
- Current balance update flow supports deposit operation.
- Sorting for account display is implemented using merge sort on the linked list.