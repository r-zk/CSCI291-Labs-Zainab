#include <stdio.h> //imports standard i/o library

#define initial_balance 1000 //defines constant for initial balance

int main() {

    //starting balance
    int balance = initial_balance;

    // Array for transactions; +ve for deposits and -ve for withdrawals
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    // Array for unprocessed transactions
    int tobeprocessed[sizeof(transactions) / sizeof(transactions[0])];
    //counts number of unprocessed transactions
    int tobeprocessed_num = 0;
    //calculates number of transactions by dividing total array size by size of one element
    int num_of_transactions = sizeof(transactions) / sizeof(transactions[0]);

    // loops through each transaction
    for (int i = 0; i < num_of_transactions; i++) {
        int transaction = transactions[i]; //gets current transaction

        // Checks for invalid withdrawals and zero balance
        if ((transaction < 0 && transaction + balance < 0) || balance == 0) {
            // Stores the unprocessed transaction and prints message to user
            tobeprocessed[tobeprocessed_num++] = transaction;
            //checks if balance is zero and reads message to user
            if (balance == 0) {
                printf("No balance left. Transactions cannot be processed.\n");
                break; //exits loop
            } else {
                //prints message about insufficient funds
                printf("Transaction %d failed: Insufficient funds for %d AED withdrawal.\n", i + 1, -transaction);
            }
        } else {
            // Processing valid transaction
            balance += transaction;
        }
    }

    // Print final balance
    printf("Your final balance is %d AED.\n", balance);

    // Unprocessed transaction printing
    if (tobeprocessed_num > 0) {
        //prints list of all unprocessed transactions
        printf("Unprocessed transactions:\n");
        for (int i = 0; i < tobeprocessed_num; i++) {
            //print each
            printf("%d ", tobeprocessed[i]);
        }
        printf("\n");
    } else {
        //if no unprocessed transaction, print message
        printf("There are no unprocessed transactions.\n");
    }

    return 0; //end program
}
