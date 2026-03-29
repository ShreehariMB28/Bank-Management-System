# Bank Management System (C)

A console-based banking application written in C with modular source/header files and binary file persistence.

## Overview

This project demonstrates core systems programming concepts:

- Structured program design with separate source and header files
- Persistent storage using binary file I/O
- Basic user authentication using username/password checks
- Record updates inside a binary database file

The application stores account data in `bank_data.dat` and provides a simple menu for account operations.

## Current Features

- Create a new bank account
- Login with username and password
- Verify account credentials before balance update
- Deposit money into an account
- Persist account records to disk in binary format

## Project Structure

```text
bank-system/
├── Makefile
├── README.md
├── bin/
├── build/
├── include/
│   └── bank.h
└── src/
	├── bank.c
	└── main.c
```

## Data Model

Each account is stored using this C structure:

```c
struct Account {
	int account_number;
	char username[50];
	char password[50];
	int balance;
};
```

Records are written directly to `bank_data.dat` using `fwrite`, and read using `fread`.

## Prerequisites

- GCC compiler
- Make utility

On Windows, this usually means using MinGW/MSYS2 or Git Bash with `gcc` and `make` available in PATH.

## Build

From the project root:

```bash
make
```

This compiles:

- `src/main.c`
- `src/bank.c`

and creates the executable:

- `bin/bank_app`

## Run

From the project root:

```bash
./bin/bank_app
```

If you are running from Windows PowerShell, you can use:

```powershell
.\bin\bank_app
```

## Menu Flow

When the app starts, you get:

1. Create Account
2. Login
3. Update Balance
4. Exit

`Update Balance` verifies username/password first, then asks for an amount to deposit.

## Output Files

- `bank_data.dat`: Binary database created in the project root at runtime

## Clean Build Artifacts

```bash
make clean
```

This removes the executable from `bin/`.

## Notes

- This is a learning-focused console project and does not include encryption/hashing for passwords.
- Input handling is basic and assumes valid user input types.
- This project is actively evolving, and more features and improvements will be added over time.