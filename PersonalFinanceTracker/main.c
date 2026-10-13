#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "models.h"
#include "logic.h"
#include "fileio.h"

// Reads and validates an integer entered by the user
int readInteger(int* value) {
    char input[32];
    char extra;

	if (fgets(input, sizeof(input), stdin) == NULL) {
		return 0;
	}

    int i = 0;

    while (input[i] != '\n' && input[i] != '\0') {
        i++;
    }
    if (input[i] == '\0') {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        printf("Input too long. Please enter a shorter number.\n");
        return 0;
    }
    if (sscanf(input, "%d %c", value, &extra) != 1) {
        return 0;
    }
   
    return 1;
}

// Reads and validates a decimal number entered by the user
int readDouble(double* value) {
	char input[32];
	char extra;
	if (fgets(input, sizeof(input), stdin) == NULL) {
		return 0;
	}
    int i = 0;

    while (input[i] != '\n' && input[i] != '\0') {
        i++;
    }
    if (input[i] == '\0') {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        printf("Input too long. Please enter a shorter number.\n");
        return 0;
    }
	if (sscanf(input, "%lf %c", value, &extra) != 1) {
		return 0;
	}

	return 1;
}


int main() {

    int menuChoice;
    int transactionType;
	int capacity = 10;
    double amount;
    double spendingLimit = 0.0;

    // Allocate memory for storing transactions
    int transactionCount = 0;
    Transaction *transactions = malloc(capacity * sizeof(Transaction));

    // Check whether memory allocation was successful
    if (transactions == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Load previously saved transactions and spending limit
    loadData(&transactions, &transactionCount, &capacity, &spendingLimit);

    do {
        // Display the menu
        printf("\nPersonal Finance Tracker\n");
        printf("1. Add Transaction\n");
        printf("2. View Transactions\n");
        printf("3. View Summary\n");
        printf("4. Set Spending Limit\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
       // Read and validate menu choice
        if (!readInteger(&menuChoice)) {
            printf("Invalid input. Please enter a valid number.\n");
            continue;
        }

        // Add a new income, expense, or investment transaction
        if (menuChoice == 1) {

            printf("Enter transaction type (1 for income, 2 for expense, 3 for investment): ");

            if (!readInteger(&transactionType)) {
                printf("Invalid transaction type. Please enter a valid number.\n");
                continue;
            }

            printf("Enter amount: ");

            if (!readDouble(&amount)) {
                printf("Invalid amount. Please enter a valid number.\n");
                continue;
            }

            if (addTransaction(&transactions, &transactionCount,
                transactionType, &capacity, amount)) {
                printf("Transaction added successfully!\n");
            }
            else {
                printf("Failed to add transaction. Please try again.\n");
            }
        }

        // Display all recorded transactions
        else if (menuChoice == 2) {
            if (transactionCount > 0) {

                printf("\n--- Transaction History ---\n");

                for (int i = 0; i < transactionCount; i++) {

                    const char* typeName;

                    if (transactions[i].type == 1) {
                        typeName = "Income";
                    }
                    else if (transactions[i].type == 2) {
                        typeName = "Expense";
                    }
                    else {
                        typeName = "Investment";
                    }
					printf("%d. Type: %s, Amount: %.2lf\n", i + 1, typeName, transactions[i].amount);

                }

            }
            else {
                printf("No transactions to display.\n");
            }
        }

        // Display a summary of financial activity
		else if (menuChoice == 3) {
			double totalIncome = calculateTotalIncome(transactions, transactionCount);
			double totalExpenses = calculateTotalExpenses(transactions, transactionCount);
			double totalInvestments = calculateTotalInvestments(transactions, transactionCount);
			double remainingLimit = calculateRemainingLimit(spendingLimit, totalExpenses);

			printf("\n--- Summary ---\n");
			printf("Total Income: %.2lf\n", totalIncome);
			printf("Total Expenses: %.2lf\n", totalExpenses);
			printf("Total Investments: %.2lf\n", totalInvestments);
            printf("Remaining Spending Limit: %.2lf\n", remainingLimit);
		}

        // Set a new spending limit
		else if (menuChoice == 4) {
			double newSpendingLimit;

			printf("Enter new spending limit: ");
			if (!readDouble(&newSpendingLimit)) {
				printf("Invalid spending limit. Please enter a valid number.\n");
				continue;
			}

			if (setSpendingLimit(&spendingLimit, newSpendingLimit)) {
				printf("Spending limit set to %.2lf\n", spendingLimit);
			}
			else {
				printf("Invalid spending limit. Please try again.\n");
			}
		}

		// Exit the program and save all data to a text file
        else if (menuChoice == 5) {
            saveData(transactions, transactionCount, spendingLimit);
            printf("Exiting the program.\n");
        }

        // Handle invalid menu choices
        else {
            printf("Invalid choice. Please try again.\n");
        }

    } while (menuChoice != 5);

    free(transactions);

    return 0;
}