#include <stdio.h>

void displayMainMenu();
void brewCoffee(int CoffeeType);
void serveCoffee(int CoffeeType);

int main() {
    int choice;

    while(1){
        displayMainMenu();
        printf("Select an option (1-3):  ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Ending Coffee Maker Simulation. Thank you. \n");
            break;

        }else if(choice < 1 || choice > 3){
            printf("Invalid Selection. Try Again. \n");

        }else{
            brewCoffee(choice);
            serveCoffee(choice);
        }
    }

    return 0;
}

void diplayMainMenu(){
    printf("\n---Coffee Menu---\n");
    printf("1. Espresso\n");
    printf("2. Cappucinno\n");
    printf("3. Mocha\n");
    printf("------------------------\n");
    
}

void brewCoffee(int CoffeeType){
    switch(CoffeeType){
        case 1:
        printf("Brewing Espresso...\n");
        break;
        case 2:
        printf("Brewing Cappucinno...\n");
        break;
        printf("Brewing Mocha...\n");
        break;
        default:
        printf("Error: Not Available.\n");
        break;
    }
}
void serveCoffee(int CoffeeType){
    switch (CoffeeType){
        case 1:
        printf("Serving Espresso. Enjoy!\n");
        break;
        case 2:
        printf("Serving Cappucinno. Enjoy!\n");
        break;
        case 3:
        printf("Serving Mocha. Enjoy!\n");
        default:
        printf("Error\n");
        break;
    }
}