#pragma once

// Represents a financial transaction
typedef struct {
    int type; // 1 = Income, 2 = Expense, 3 = Investment
    double amount; // Transaction amount
} Transaction;
