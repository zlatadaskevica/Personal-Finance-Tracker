# Personal Finance Tracker

A simple console-based application developed in C for tracking personal finances.

## Features

- Add income, expense, and investment transactions.
- View transaction history.
- Display financial summaries.
- Set a spending limit and calculate the remaining amount.
- Save and load financial data using a local text file.
- Validate user input and handle invalid data.

## Project Structure

- `main.c` — Menu, user interaction, and program execution.
- `logic.c` / `logic.h` — Transaction management, validation, and financial calculations.
- `models.c` / `models.h` — Transaction data structure.
- `fileio.c` / `fileio.h` — Saving and loading financial data.

## Compilation and Execution

Compile using GCC from the directory containing the source files:

```bash
gcc -std=c11 -Wall -Wextra main.c logic.c models.c fileio.c -o PersonalFinanceTracker
```

Run the application:

```bash
./PersonalFinanceTracker
```

The application stores financial data locally in `data.txt`.
