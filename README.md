# Bank Management System in C

A console-based bank management application written in C with linked-list account storage in memory and binary persistence on disk.

## Overview

At startup, the app loads account records from `bank_data.dat` into a linked list. During execution, all operations happen in memory. On exit, records are written back to disk and allocated nodes are freed.

## Current Features

- Create account with duplicate account number check
- Login-based balance check using username and password
- Deposit money after credential verification
- Withdraw money with insufficient-balance validation
- Display all accounts sorted by balance (ascending)
- Persist all accounts to a binary file between runs

## Change Notes (Based on Current Code)

The following points reflect what is currently implemented across `src/main.c`, `src/bank.c`, and `include/bank.h`:

- Menu now has 6 options, including separate Deposit and Withdraw flows
- Withdraw flow exists and checks requested amount against balance
- Balance check is handled through `login()`
- Account display is sorted using linked-list merge sort before printing
- Data file persistence uses `load_data()` and `save_exit()` with `fread` and `fwrite`
- Project ignores generated files and folders via `.gitignore` (`bin/`, `build/`, `*.dat`, `*.exe`, `*.o`)

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

## Data Model

```c
struct Account {
    int account_number;
    char username[50];
    char password[50];
    int balance;
};
```

Accounts are stored in a singly linked list using `struct Node`.

## Runtime Menu

1. Create Account
2. Check Balance
3. Deposit Money
4. Withdraw Money
5. Display All Accounts
6. Exit

## Build and Run

## Prerequisites

- GCC
- Make

## Build with Makefile

```bash
make
```

Current Makefile output target:

- `bin/bank_app`

## Manual Build (Windows)

```bash
gcc src/main.c src/bank.c -o bin/bank_app.exe
```

## Run (PowerShell)

```powershell
.\bin\bank_app.exe
```

## Run (Git Bash/Linux/macOS)

```bash
./bin/bank_app
```

## Clean

```bash
make clean
```

## Data Persistence

- File: `bank_data.dat` in project root
- Startup: `load_data()` loads all saved records into memory
- Exit: `save_exit()` writes all records to disk, frees memory, then exits

## Limitations

- Passwords are stored as plain text
- Input handling assumes correct input types
- No account deletion or update-profile flow
- No transaction history or audit log