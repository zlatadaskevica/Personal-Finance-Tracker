#define _CRT_SECURE_NO_WARNINGS
#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include "logic.h"

// Saves all financial data to a text file
void saveData(Transaction transactions[], int transactionCount, double spendingLimit) {
	FILE* file = fopen("data.txt", "w");
	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}
	fprintf(file, "%d\n", transactionCount);
	fprintf(file, "%.2f\n", spendingLimit);
	for (int i = 0; i < transactionCount; i++) {
		fprintf(file, "%d %.2f\n", transactions[i].type, transactions[i].amount);
	}
	fclose(file);
}

// Loads financial data from a text file
void loadData(Transaction** transactions, int* transactionCount, int* capacity, double* spendingLimit) {
	FILE* file = fopen("data.txt", "r");
	if (file == NULL) {
		printf("Error opening file for reading.\n");
		*transactionCount = 0;
		*spendingLimit = 0.0;
		return;
	}

	if (fscanf(file, "%d", transactionCount) != 1) {
		printf("Invalid transaction count in file.\n");
		*transactionCount = 0;
		fclose(file);
		return;
	}
	if (*transactionCount < 0 || *transactionCount > 10000) {
		printf("Invalid transaction count in file.\n");
		*transactionCount = 0;
		fclose(file);
		return;
	}

	// Increase memory capacity if saved transactions exceed current capacity
	int newCapacity = *transactionCount;

	if (*transactionCount > *capacity) {
		Transaction* temp;
		temp = realloc(*transactions, newCapacity * sizeof(Transaction));
		if (temp == NULL) {
			printf("Memory allocation failed.\n");
			fclose(file);
			return;
		}
		*transactions = temp;
		*capacity = newCapacity;
	}
	if (fscanf(file, "%lf", spendingLimit) != 1) {
		printf("Invalid spending limit in file.\n");
		*transactionCount = 0;
		*spendingLimit = 0.0;
		fclose(file);
		return;
	}
	if (*spendingLimit < 0) {
		printf("Invalid spending limit in file.\n");
		*transactionCount = 0;
		*spendingLimit = 0.0;
		fclose(file);
		return;
	}
	// Read and validate each saved transaction
	for (int i = 0; i < *transactionCount; i++) {
		if (fscanf(file, "%d %lf",
			&((*transactions)[i].type),
			&((*transactions)[i].amount)) != 2) {

			printf("Invalid transaction data in file.\n");
			*transactionCount = 0;
			*spendingLimit = 0.0;
			fclose(file);
			return;
		}
		if (isValidTransactionType((*transactions)[i].type) == 0 || !isValidAmount((*transactions)[i].amount)) {
			printf("Invalid transaction data in file.\n");
			*transactionCount = 0;
			*spendingLimit = 0.0;
			fclose(file);
			return;
		}
	}
	fclose(file);
}