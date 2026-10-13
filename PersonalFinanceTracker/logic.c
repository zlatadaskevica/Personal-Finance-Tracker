#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

// Checks whether the transaction amount is positive
int isValidAmount(double amount) {
	if (amount > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

// Checks whether the transaction type is valid
int isValidTransactionType(int type) {
	if (type == 1 || type == 2 || type == 3) {
		return 1;
	}
	else {
		return 0;
	}
}

// Adds a valid transaction to the transaction array
int addTransaction(Transaction **transactions, int* transactionCount, int type, int* capacity, double amount) {
	if (!isValidTransactionType(type) || !isValidAmount(amount)) {
		return 0;
	}

	if (*transactionCount >= *capacity) {
		Transaction *temp;

		int newCapacity = *capacity * 2;
		temp = realloc(*transactions, newCapacity * sizeof(Transaction));
		if (temp == NULL) {
			printf("Memory allocation failed.\n");
			return 0;
		}
		*transactions = temp;
		*capacity = newCapacity;
	}
	
	(*transactions)[*transactionCount].type = type;
	(*transactions)[*transactionCount].amount = amount;
	(*transactionCount)++;

	return 1;
}

// Calculates the total amount of income transactions
double calculateTotalIncome(Transaction transactions[], int transactionCount) {
	double totalIncome = 0;

	for (int i = 0; i < transactionCount; i++) {
		if (transactions[i].type == 1) {
			totalIncome = totalIncome + transactions[i].amount;
		}
	}
	return totalIncome;
}

// Calculates the total amount of expense transactions
double calculateTotalExpenses(Transaction transactions[], int transactionCount) {
	double totalExpenses = 0;

	for (int i = 0; i < transactionCount; i++) {
		if (transactions[i].type == 2) {
			totalExpenses = totalExpenses + transactions[i].amount;
		}
	}

	return totalExpenses;
}

// Calculates the total amount of investment transactions
double calculateTotalInvestments(Transaction transactions[], int transactionCount) {
	double totalInvestments = 0;

	for (int i = 0; i < transactionCount; i++) {
		if (transactions[i].type == 3) {
			totalInvestments = totalInvestments + transactions[i].amount;
		}
	}

	return totalInvestments;
}

// Checks whether the spending limit is a positive value
int isValidSpendingLimit(double spendingLimit) {
	if (spendingLimit > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

// Sets a new spending limit if the entered value is valid
int setSpendingLimit(double* limit, double newLimit) {
	if (isValidSpendingLimit(newLimit)) {
		*limit = newLimit;
		return 1;
	}
	else {
		return 0;
	}
}

// Calculates the remaining spending limit after expenses
double calculateRemainingLimit(double spendingLimit, double totalExpenses) {
	return spendingLimit - totalExpenses;
}