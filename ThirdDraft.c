#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// defining variables //
#define admin_password 12345   // administrator password to access admin mode //

// price in AED //
#define total_amount_espresso 3.5      // espresso price //
#define total_amount_cappucino 4.5     // cappucino price //
#define total_amount_mocha 5.5         // mocha price //

// beans //
#define espresso_beans_grams 8    // espresso beans amount in grams //
#define cappuccino_beans_grams 8  // cappuccino beans amount in grams //
#define mocha_beans_grams 8       // mocha beans amount in grams //

// water //
#define espresso_water_millilitres 30    // espresso water amount in millilitres //
#define cappuccino_water_millilitres 30  // cappuccino water amount in millilitres //
#define mocha_water_millilitres 39       // mocha water amount in millilitres //

// milk //
#define espresso_milk_millilitres 0  // espresso milk amount in millilitres //
#define cappuccino_milk_millilitres 70 // cappuccino milk amount in millilitres //
#define mocha_milk_millilitres 160  // mocha milk amount in millilitres //

// syrup //
#define espresso_syrup_millilitres 0  // espresso syrup amount in millilitres //
#define cappuccino_syrup_millilitres 0 // cappuccino syrup amount in millilitres //
#define mocha_syrup_millilitres 30    // mocha syrup amount in millilitres //

// low threshold //
#define low_threshold_beans 50 // alert for beans //
#define low_threshold_water 100 // alert for water //
#define low_threshold_milk 150 // alert for milk //
#define low_threshold_syrup 50 // alert for syrup //

// global variables //
float total_amount = 0.0;
float espresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;
int coffee_beans = 240; // initial quantity beans
int water = 990; // initial quantity water
int milk = 2300; // initial quantity milk
int chocolate_syrup = 300; // initial quantity syrup

// Function prototypes //
void make_espresso();
void make_cappuccino();
void make_mocha();
void check_ingredients();
void display_main_menu();
void admin_mode();
void replenish_ingredients();
void change_coffee_price();
void display_and_reset_sales();
void display_ingredient_quantities();
void process_payment(char *coffee_name, float price, int coffee_beans_required, int water_required, int milk_required, int chocolate_required);

int confirm_selection(char *coffee_name, float price);

// Main function //
int main() {
    int choice;

    while (1) {
        printf("\n--- Coffee Maker Simulator Main Menu ---\n");
        printf("1. Order a Coffee\n");
        printf("2. Admin Mode\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_main_menu();
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                printf("Exiting Simulator.\n");
                return 0;
            default:
                printf("Error: Not an Option.\n");
        }
    }
    return 0;
}

// Functions definitions //
void display_main_menu() {
    int coffee_choice;
    float price = 0.0;
    int confirmed = 0;

    while (1) {
        printf("\nSelect an Option: \n");
        if (coffee_beans >= espresso_beans_grams && water >= espresso_water_millilitres) {
            printf("1. Espresso - 3.5 AED\n");
        } else {
            printf("Unavailable due to temporarily insufficient ingredients\n");
        }
        if (coffee_beans >= cappuccino_beans_grams && water >= cappuccino_water_millilitres && milk >= cappuccino_milk_millilitres) {
            printf("2. Cappuccino - 4.5 AED\n");
        } else {
            printf("Unavailable due to temporarily insufficient ingredients\n");
        }
        if (coffee_beans >= mocha_beans_grams && water >= mocha_water_millilitres && milk >= mocha_milk_millilitres && chocolate_syrup >= mocha_syrup_millilitres) {
            printf("3. Mocha - 5.5 AED\n");
        } else {
            printf("Unavailable due to temporarily insufficient ingredients\n");
        }
        printf("4. Exit\n");
        printf("Enter your coffee choice: ");
        scanf("%d", &coffee_choice);

        switch (coffee_choice) {
            case 1:
                if (coffee_beans >= espresso_beans_grams && water >= espresso_water_millilitres) {
                    price = total_amount_espresso;
                    confirmed = confirm_selection("Espresso", price);
                    if (confirmed) process_payment("Espresso", price, espresso_beans_grams, espresso_water_millilitres, espresso_milk_millilitres, espresso_syrup_millilitres);
                } else {
                    printf("Espresso is unavailable due to temporarily insufficient ingredients.\n");
                }
                break;
            case 2:
                if (coffee_beans >= cappuccino_beans_grams && water >= cappuccino_water_millilitres && milk >= cappuccino_milk_millilitres) {
                    price = total_amount_cappucino;
                    confirmed = confirm_selection("Cappuccino", price);
                    if (confirmed) process_payment("Cappuccino", price, cappuccino_beans_grams, cappuccino_water_millilitres, cappuccino_milk_millilitres, cappuccino_syrup_millilitres);
                } else {
                    printf("Cappuccino is unavailable due to temporarily insufficient ingredients.\n");
                }
                break;
            case 3:
                if (coffee_beans >= mocha_beans_grams && water >= mocha_water_millilitres && milk >= mocha_milk_millilitres && chocolate_syrup >= mocha_syrup_millilitres) {
                    price = total_amount_mocha;
                    confirmed = confirm_selection("Mocha", price);
                    if (confirmed) process_payment("Mocha", price, mocha_beans_grams, mocha_water_millilitres, mocha_milk_millilitres, mocha_syrup_millilitres);
                } else {
                    printf("Mocha is unavailable due to temporarily insufficient ingredients.\n");
                }
                break;
            case 4:
                return; // Exit the function
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to confirm the user's selection //
int confirm_selection(char *coffee_name, float price) {
    int confirmation;
    printf("You selected %s for %.2f AED. Confirm? (1 for Yes, 0 for No): ", coffee_name, price);
    scanf("%d", &confirmation);
    return confirmation == 1;
}

// Function to process the payment and update the ingredients //
void process_payment(char *coffee_name, float price, int coffee_beans_required, int water_required, int milk_required, int chocolate_required) {
    float amount_paid = 0.0, coin;

    printf("Please pay %.2f AED.\n", price);
    while (amount_paid < price) {
        printf("Insert coin (1 or 0.5 AED): ");
        scanf("%f", &coin);

        if (coin == 1.0 || coin == 0.5) {
            amount_paid += coin;
        } else {
            printf("Invalid coin. Please collect it back and insert a valid coin.\n");
        }
    }

    float change = amount_paid - price;
    printf("Thank you for purchasing %s! Price: %.2f AED, Paid: %.2f AED, Change: %.2f AED\n", coffee_name, price, amount_paid, change);

    // Update ingredients //
    coffee_beans -= coffee_beans_required;
    water -= water_required;
    milk -= milk_required;
    chocolate_syrup -= chocolate_required;
    total_amount += price;

    // Check if any ingredient has fallen below the threshold //
    check_ingredients();
}

void check_ingredients() {
    if (coffee_beans <= low_threshold_beans) {
        printf("Alert: Low on coffee beans!\nRefill Required\n");
    }
    if (water <= low_threshold_water) {
        printf("Alert: Low on water!\nRefill Required\n");
    }
    if (milk <= low_threshold_milk) {
        printf("Alert: Low on milk!\nRefill Required\n");
    }
    if (chocolate_syrup <= low_threshold_syrup) {
        printf("Alert: Low on chocolate syrup!\nRefill Required\n");
    }
}

// Admin Mode //
void admin_mode() {
    int password;
    int option;

    printf("Enter Admin Password: ");
    scanf("%d", &password);

    if (password == admin_password) {
        while (1) {
            printf("\n--- Admin Menu ---\n");
            printf("1. Replenish Ingredients\n");
            printf("2. Change Coffee Prices\n");
            printf("3. Display and Reset Total Sales\n");
            printf("4. Display Current Ingredient Quantities\n");
            printf("5. Exit Admin Mode\n");
            printf("Enter your choice: ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    replenish_ingredients();
                    break;
                case 2:
                    change_coffee_price();
                    break;
                case 3:
                    display_and_reset_sales();
                    break;
                case 4:
                    display_ingredient_quantities();
                    break;
                case 5:
                    return; // Exit admin mode
                default:
                    printf("Invalid option. Please try again.\n");
            }
        }
    } else {
        printf("Incorrect Password.\n");
    }
}

// Function to replenish ingredients //
void replenish_ingredients() {
    printf("Enter amount of coffee beans to add (g): ");
    int beans_add;
    scanf("%d", &beans_add);
    coffee_beans += beans_add;

    printf("Enter amount of water to add (ml): ");
    int water_add;
    scanf("%d", &water_add);
    water += water_add;

    printf("Enter amount of milk to add (ml): ");
    int milk_add;
    scanf("%d", &milk_add);
    milk += milk_add;

    printf("Enter amount of chocolate syrup to add (ml): ");
    int syrup_add;
    scanf("%d", &syrup_add);
    chocolate_syrup += syrup_add;

    printf("Ingredients replenished.\n");
}

// Function to change coffee prices //
void change_coffee_price() {
    printf("Enter new price for Espresso: ");
    scanf("%f", &espresso_price);

    printf("Enter new price for Cappuccino: ");
    scanf("%f", &cappuccino_price);

    printf("Enter new price for Mocha: ");
    scanf("%f", &mocha_price);

    printf("Prices updated.\n");
}

// Function to display and reset total sales //
void display_and_reset_sales() {
    printf("Total sales: %.2f AED\n", total_amount);
    total_amount = 0.0;
}

// Function to display current ingredient quantities //
void display_ingredient_quantities() {
    printf("Coffee beans: %d g\n", coffee_beans);
    printf("Water: %d ml\n", water);
    printf("Milk: %d ml\n", milk);
    printf("Chocolate syrup: %d ml\n", chocolate_syrup);
}
