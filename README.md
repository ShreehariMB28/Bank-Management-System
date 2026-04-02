# 🏦 Bank Management System

A console-based bank management application written in **C**, using a **linked-list** data structure for in-memory account storage and **binary file** persistence on disk.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Data Model](#data-model)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Build](#build)
  - [Run](#run)
  - [Clean](#clean)
- [Usage](#usage)
- [Data Persistence](#data-persistence)
- [Tech Stack](#tech-stack)
- [Limitations](#limitations)
- [License](#license)

---

## Overview

The system loads account records from `bank_data.dat` into a singly linked list at startup. All operations — account creation, login, deposits, withdrawals, and display — are performed on the in-memory list. When the user exits, every record is written back to the binary file and all allocated memory is freed.

---

## Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Create Account** | Register a new account with a unique account number, username, and password |
| 2 | **Check Balance** | Log in with credentials to view the current balance |
| 3 | **Deposit Money** | Add funds to an account after credential verification |
| 4 | **Withdraw Money** | Withdraw funds with insufficient-balance validation |
| 5 | **Display All Accounts** | View every account sorted by balance (ascending) using merge sort |
| 6 | **Data Persistence** | Automatically save and load accounts from a binary file between sessions |

---

## Project Structure

```
bank-system/
├── Makefile            # Build automation
├── README.md
├── .gitignore
├── include/
│   └── bank.h          # Header — structs & function declarations
├── src/
│   ├── main.c          # Entry point & menu loop
│   └── bank.c          # Core logic (CRUD, sorting, file I/O)
├── bin/                # Compiled binary output (git-ignored)
└── build/              # Intermediate build files (git-ignored)
```

---

## Data Model

```c
struct Account {
    int account_number;
    char username[50];
    char password[50];
    int balance;
};
```

Accounts are stored in a **singly linked list** (`struct Node`) for dynamic, heap-based management.

---

## Getting Started

### Prerequisites

- **GCC** (MinGW on Windows, or any standard C compiler)
- **Make** (optional — you can compile manually)

### Build

**Using Make:**

```bash
make
```

This compiles `src/main.c` and `src/bank.c` and outputs the binary to `bin/bank_app`.

**Manual compilation (Windows):**

```bash
gcc -Wall src/main.c src/bank.c -o bin/bank_app.exe
```

### Run

**PowerShell / CMD:**

```powershell
.\bin\bank_app.exe
```

**Git Bash / Linux / macOS:**

```bash
./bin/bank_app
```

### Clean

```bash
make clean
```

---

## Usage

On launch you'll see the interactive menu:

```
=== Bank Management System ===
1. Create Account
2. Check Balance
3. Deposit Money
4. Withdraw Money
5. Display All Accounts
6. Exit
Choose an option:
```

Select an option by entering its number. Follow the on-screen prompts for each operation.

---

## Data Persistence

| Event | Action |
|-------|--------|
| **Startup** | `load_data()` reads `bank_data.dat` and builds the linked list |
| **Exit (option 6)** | `save_exit()` writes all accounts back to `bank_data.dat`, frees memory, and terminates |

> The data file is created automatically on first exit if it doesn't already exist.

---

## Tech Stack

- **Language:** C (C99)
- **Data Structure:** Singly Linked List
- **Sorting Algorithm:** Merge Sort (linked-list variant with fast/slow pointer split)
- **File I/O:** Binary read/write (`fread` / `fwrite`)
- **Build Tool:** GNU Make

---

## Limitations

- Passwords are stored in **plain text** (no hashing or encryption)
- Input handling assumes correct data types (no robust input validation)
- No account deletion or profile-update functionality
- No transaction history or audit logging
- Single-user console application (no concurrency)

---

## License

This project is open-source and available for educational purposes.