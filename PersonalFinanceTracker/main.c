#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Maximum number of transactions that can be stored
#define MAX_TRANSACTIONS 100

int main() {

    int menuChoice;
    int transactionType;
    double amount;

    // Store transaction types and corresponding amounts
    int transactionTypes[MAX_TRANSACTIONS];
    double amounts[MAX_TRANSACTIONS];
    int transactionCount = 0;

    do {
        // Display the menu
        printf("\nPersonal Finance Tracker\n");
        printf("1. Add Transaction\n");
        printf("2. View Transactions\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        // Read user choice
        scanf("%d", &menuChoice);

        // Add a new income or expense transaction
        if (menuChoice == 1) {
            if (transactionCount < MAX_TRANSACTIONS) {
                printf("Enter transaction type (1 for income, 2 for expense): ");
                scanf("%d", &transactionType);

                if (transactionType == 1 || transactionType == 2) {
                    printf("Enter amount: ");
                    scanf("%lf", &amount);

                    if (amount > 0) {
                        transactionTypes[transactionCount] = transactionType;
                        amounts[transactionCount] = amount;

                        transactionCount++;

                        printf("Transaction added successfully!\n");
                    }
                    else {
                        printf("Invalid amount. Please enter a positive value.\n");
                    }
                }
                else {
                    printf("Invalid transaction type. Please enter 1 for income or 2 for expense.\n");
                }
            }
            else {
                printf("History is full. Maximum limit of %d transactions reached.\n", MAX_TRANSACTIONS);
            }
        }

        // Display all recorded transactions
        else if (menuChoice == 2) {
            if (transactionCount > 0) {

                printf("\n--- Transaction History ---\n");

                for (int i = 0; i < transactionCount; i++) {
                    printf("%d. Type: %s | Amount: $%.2f\n",
                        i + 1,
                        (transactionTypes[i] == 1) ? "Income" : "Expense",
                        amounts[i]);
                }

            }
            else {
                printf("No transactions to display.\n");
            }
        }

        // Exit the program
        else if (menuChoice == 3) {
            printf("Exiting the program.\n");
        }

        // Handle invalid menu choices
        else {
            printf("Invalid choice. Please try again.\n");
        }

    } while (menuChoice != 3);

    return 0;
}