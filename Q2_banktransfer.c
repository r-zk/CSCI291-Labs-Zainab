#include <stdio.h>

#define initial_balance 1000

int main() {

    int balance = initial_balance;

    // Array for transactions
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    // Array for unprocessed transactions
    int tobeprocessed[sizeof(transactions) / sizeof(transactions[0])];
    int tobeprocessed_num = 0;
    int num_of_transactions = sizeof(transactions) / sizeof(transactions[0]);

    for (int i = 0; i < num_of_transactions; i++) {
        int transaction = transactions[i];

        // Checks for invalid withdrawals and zero balance
        if ((transaction < 0 && transaction + balance < 0) || balance == 0) {
            // Stores the unprocessed transaction and prints message to user
            tobeprocessed[tobeprocessed_num++] = transaction;
            if (balance == 0) {
                printf("No existing balance.\nTransactions cannot be processed at this time.\n");
                break;
            } else {
                printf("Transaction %d: %d AED withdrawal is not valid, insufficient balance.\n", i + 1, -transaction);
            }
        } else {
            // Processing valid transaction
            balance += transaction;
        }
    }

    // Print final balance
    printf("Final balance: %d AED\n", balance);

    // Unprocessed transaction printing
    if (tobeprocessed_num > 0) {
        printf("Unprocessed transactions:\n");
        for (int i = 0; i < tobeprocessed_num; i++) {
            printf("%d ", tobeprocessed[i]);
        }
        printf("\n");
    } else {
        printf("There are no unprocessed transactions.\n");
    }

    return 0;
}
