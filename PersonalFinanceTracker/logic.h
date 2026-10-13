#pragma once
#include "models.h"

// Validation
int isValidAmount(double amount);
int isValidTransactionType(int type);
int isValidSpendingLimit(double spendingLimit);

// Transaction management
int setSpendingLimit(double* limit, double newLimit);
int addTransaction(Transaction **transactions, int* transactionCount, int type, int* capacity, double amount);

// Financial calculations
double calculateTotalIncome(Transaction transactions[], int transactionCount);
double calculateTotalExpenses(Transaction transactions[], int transactionCount);
double calculateTotalInvestments(Transaction transactions[], int transactionCount);
double calculateRemainingLimit(double spendingLimit, double totalExpenses);

