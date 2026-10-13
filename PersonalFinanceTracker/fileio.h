#pragma once
#include "models.h"

// Saves transactions and spending limit to a text file
void saveData(Transaction transactions[], int transactionCount, double spendingLimit);

// Loads saved transactions and spending limit from a text file
void loadData(Transaction** transactions, int* transactionCount, int* capacity, double* spendingLimit);