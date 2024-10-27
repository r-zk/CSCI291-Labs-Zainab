#include <stdio.h> // import standard I/O functions
#include <stdlib.h> // import standard library functions
#include <time.h> // imports functions for manipulating date and time

// defining variables //
#define admin_password 12345   // administrator password to access admin mode //

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
#define low_threshold_beans 50 // low threshold for beans //
#define low_threshold_water 100 // low threshold for water //
#define low_threshold_milk 150 // low threshold for milk //
#define low_threshold_syrup 50 // low threshold for syrup //

// global variables //
float total_amount = 0.0; // stores total sales amount
float espresso_price = 3.5; // espresso price
float cappuccino_price = 4.5; // cappuccino price
float mocha_price = 5.5; //mocha price
int coffee_beans = 240; // initial quantity beans
int water = 990; // initial quantity water
int milk = 2300; // initial quantity milk
int chocolate_syrup = 300; // initial quantity syrup

// function prototypes //
void make_espresso(); // brews espresso
void make_cappuccino(); //brews cappuccino
void make_mocha(); // brews mocha
void check_ingredients(); //checks ingredient availability
void display_main_menu(); //main menu function
void admin_mode(); // admin mode function
void replenish_ingredients(); //replenishes ingredients
void change_coffee_price(); //changes coffee pricing
void display_and_reset_sales(); //resets sales
void display_ingredient_quantities(); //displays ingredient quantities
void process_payment(char *coffee_name, float price, int coffee_beans_required, int water_required, int milk_required, int chocolate_required); //processes payments

int confirm_selection(char *coffee_name, float price); //confirms coffee selection

// main function //
int main() {
    srand(time(0));  // initialize random seed for replenishment
    int choice; //variable to store user menu choice

    while (1) { // main loop for simulator
        printf("\n--- Coffee Maker Simulator Main Menu ---\n"); // display main menu header
        printf("1. Order a Coffee\n"); // option for ordering coffee
        printf("2. Admin Mode\n"); //option to access admin mode
        printf("3. Exit\n"); //option to exit the simulator
        printf("Enter your choice: "); // asks user for choice
        scanf("%d", &choice); // reads user choice

        switch (choice) { //process user menu choice
            case 1: //case for ordering coffee
                display_main_menu(); //display coffee menu
                break; // exits switch
            case 2: // case for accessing admin mode
                admin_mode(); //access admin mode
                break; // exits the switch
            case 3: // case for exiting simulator
                printf("Exiting Simulator.\n"); // notifies the user that simulation is being exited
                return 0; //exit the program
            default: // case for invalid choice
                printf("Error: Not an Option.\n"); //invalid choice handling
        }
    }
    return 0; // infinite loop end
}

// function definitions
// function to display coffee selection menu
void display_main_menu() { // define function to display main menu
    int coffee_choice; //variable to store user coffee choice
    float price = 0.0; // varible to store coffee price
    int confirmed = 0; // variable to see if selection is confirmed

    while (1) { // starts infinite main menu loop
        printf("\nSelect an Option: \n"); // asks user to select option

        // checks if ingredients are available before displaying coffee options
        if (coffee_beans >= espresso_beans_grams && water >= espresso_water_millilitres) { // check if ingredients for espresso are available
            printf("1. Espresso - %.2f AED\n", espresso_price); //display espresso option
        }
        if (coffee_beans >= cappuccino_beans_grams && water >= cappuccino_water_millilitres && milk >= cappuccino_milk_millilitres) { //check if ingredients for espresso are available
            printf("2. Cappuccino - %.2f AED\n", cappuccino_price); //display cappuccino option
        }
        if (coffee_beans >= mocha_beans_grams && water >= mocha_water_millilitres && milk >= mocha_milk_millilitres && chocolate_syrup >= mocha_syrup_millilitres) { //check if ingredients for mocha are available
            printf("3. Mocha - %.2f AED\n", mocha_price); //display mocha option
        }
        printf("4. Exit\n"); // option to exit main menu
        printf("Enter your coffee choice: "); // asks user for coffee choice
        scanf("%d", &coffee_choice); // reads user coffee choice

        switch (coffee_choice) { // process's user choice
            case 1: //case for espresso
                if (coffee_beans >= espresso_beans_grams && water >= espresso_water_millilitres) { // check ingredient availability
                    price = espresso_price; //set espresso price
                    confirmed = confirm_selection("Espresso", price); //confirms choice
                    if (confirmed) process_payment("Espresso", price, espresso_beans_grams, espresso_water_millilitres, espresso_milk_millilitres, espresso_syrup_millilitres); //processes payment if true
                } else {
                    printf("Espresso is unavailable due to temporarily insufficient ingredients.\n"); //notifies user if ingredients are insufficent
                }
                break; // exits the switch
            case 2: //case for cappuccino
                if (coffee_beans >= cappuccino_beans_grams && water >= cappuccino_water_millilitres && milk >= cappuccino_milk_millilitres) { //checks ingredient availiabilty
                    price = cappuccino_price; //sets cappuccino price
                    confirmed = confirm_selection("Cappuccino", price); //confirms selection
                    if (confirmed) process_payment("Cappuccino", price, cappuccino_beans_grams, cappuccino_water_millilitres, cappuccino_milk_millilitres, cappuccino_syrup_millilitres); //processes payment if true
                } else {
                    printf("Cappuccino is unavailable due to temporarily insufficient ingredients.\n"); //notifies user if ingredients are insufficent
                }
                break; // exits switch
            case 3: // case for mocha
                if (coffee_beans >= mocha_beans_grams && water >= mocha_water_millilitres && milk >= mocha_milk_millilitres && chocolate_syrup >= mocha_syrup_millilitres) { //check availibility of ingredients
                    price = mocha_price; // set price for mocha
                    confirmed = confirm_selection("Mocha", price); // confirms choice
                    if (confirmed) process_payment("Mocha", price, mocha_beans_grams, mocha_water_millilitres, mocha_milk_millilitres, mocha_syrup_millilitres); // processes payment if true
                } else {
                    printf("Mocha is unavailable due to temporarily insufficient ingredients.\n"); //notifies user if ingredients are insufficent
                }
                break; // exits switch
            case 4: // case for exiting menu
                return; // exits the function
            default: // case for invild choice
                printf("Invalid choice! Please try again.\n"); //notify user of invalid choice
        }
    }
}

// function to confirm the user's selection //
int confirm_selection(char *coffee_name, float price) {
    int confirmation;
    printf("You selected %s for %.2f AED. Confirm? (1 for Yes, 0 for No): ", coffee_name, price);
    scanf("%d", &confirmation);
    return confirmation == 1; //return true if user confirms selection
}

// function to process the payment and update the ingredients //
void process_payment(char *coffee_name, float price, int coffee_beans_required, int water_required, int milk_required, int chocolate_required) {
    float amount_paid = 0.0, coin; // variables to track amount paid and coin input

    printf("Please pay %.2f AED.\n", price); // asks user for payment
    while (amount_paid < price) { //loop until amount paid is sufficient
        printf("Insert coin (1 or 0.5 AED): "); // asks user to insert coin
        scanf("%f", &coin); // reads coin input

        if (coin == 1.0 || coin == 0.5) { // check if insertred coin is valid
            amount_paid += coin; //add valid coin to the amount paid
        } else {
            printf("Invalid coin. Please collect it back and insert a valid coin.\n"); // notifies user of invalid coin
        }
    }

    float change = amount_paid - price; // calculate change to be retured
    printf("Thank you for purchasing %s! Price: %.2f AED, Paid: %.2f AED, Change: %.2f AED\n", coffee_name, price, amount_paid, change); //shows transaction details, thanks user

    // update ingredients and process payment//
    coffee_beans -= coffee_beans_required; // deduct required beans
    water -= water_required; // deduct required water
    milk -= milk_required; // deduct required milk
    chocolate_syrup -= chocolate_required; // deduct required syrup
    total_amount += price; // update total sales amount

    // check if any ingredient has fallen below the threshold //
    check_ingredients(); // call function to check ingredient levels
}

// function to check if any ingredient is below the threshold and alert if needed
void check_ingredients() { //define function to check ingredient levels
    if (coffee_beans <= low_threshold_beans) { //  check if coffee beans below threshold
        printf("Alert: Low on coffee beans!\nRefill Required\n"); // notify  user of low beans
    }
    if (water <= low_threshold_water) { // check if water is below threshold
        printf("Alert: Low on water!\nRefill Required\n"); // notify  user of low water
    }
    if (milk <= low_threshold_milk) { // check if milk is below threshold
        printf("Alert: Low on milk!\nRefill Required\n"); //notify  user of low milk
    }
    if (chocolate_syrup <= low_threshold_syrup) { //check if syrup is below threshold
        printf("Alert: Low on chocolate syrup!\nRefill Required\n"); // notify  user of low syrup
    }
}

// Admin Mode //
void admin_mode() { // define function for admin mode
    int password; // variable to store admin password input
    int option; // variable to store the menu option selected by the admin

    printf("Enter Admin Password: "); // asks user for admin password
    scanf("%d", &password); //reads password input from user

    if (password == admin_password) { // check if password entered matches admin password
        while (1) { // starts an infinite loop for admin mode
            printf("\n--- Admin Menu ---\n"); // display admin menu header
            printf("1. Replenish Ingredients\n"); // option fro replenishing ingredients
            printf("2. Change Coffee Prices\n"); // option to change coffee prices
            printf("3. Display and Reset Total Sales\n"); // option to display and reset sales
            printf("4. Display Current Ingredient Quantities\n"); // option to display ingredient quantities
            printf("5. Exit Admin Mode\n"); // option to exit admin mode
            printf("Enter your choice: "); // ask for user's choice
            scanf("%d", &option); // read the choice input

            switch (option) { // evaluate the chosen option 
                case 1: // case for ingredient replenishing
                    replenish_ingredients(); //function called to replenish ingredients
                    break; // exits switch
                case 2: // case for display and resetting sales
                    change_coffee_price(); // calling function to display and reset the sales
                    break; // exits the switch
                case 3: // case for displaying  and resetting sales
                    display_and_reset_sales(); // function called display and reset sales
                    break; // exit the switch
                case 4: // case to display ingredient quantities
                    display_ingredient_quantities(); // calls function to display ingredient quantities
                    break; // exits the switch
                case 5: // case for exiting admin mode
                    return; // Exit admin mode
                default: // case for invalid options
                    printf("Invalid option. Please try again.\n"); // notifies the user of the invild choice
            }
        }
    } else {
        printf("Incorrect Password.\n"); //notfies user of incorrect password
    }
}

// function to replenish ingredients //
void replenish_ingredients() {
    coffee_beans += rand() % 100 + 50;     // add random 50-149 g of beans
    water += rand() % 200 + 100;           // add random 100-299 ml of water
    milk += rand() % 300 + 150;            // add random 150-449 ml of milk
    chocolate_syrup += rand() % 50 + 25;   // add random 25-74 ml of syrup

    printf("Ingredients replenished randomly.\n"); // notifies user that ingredients have been replenished
}

// function to change coffee prices //
void change_coffee_price() { //define function to change coffee price
    int choice; // variable to store user choice of coffee type
    printf("Select coffee to update price:\n1. Espresso\n2. Cappuccino\n3. Mocha\nChoice: "); // asks user for coffee type
    scanf("%d", &choice); // reads user choice

    switch (choice) { // evaluate user choice
        case 1: // case for espresso
            printf("Enter new price for Espresso: "); //asks for new price
            scanf("%f", &espresso_price); //reads new price
            break; //exit switch
        case 2: // case for cappuccino
            printf("Enter new price for Cappuccino: "); // asks for new price
            scanf("%f", &cappuccino_price); // reads new price
            break; // exits switch
        case 3: // case for mocha
            printf("Enter new price for Mocha: "); // asks for new price
            scanf("%f", &mocha_price); // reads new price
            break; // exits switch
        default: // case for invalid choice
            printf("Invalid choice.\n"); // notify user of invalid choice
    }
    printf("Price updated.\n"); // notify user that price was updated
}

// Function to display and reset total sales //
void display_and_reset_sales() { //define function to display and reset sales
    int reset; //variable to store user decision to reset sales
    printf("Total sales: %.2f AED\n", total_amount); //displays total sales amount
    printf("Do you want to reset sales? (1 for Yes, 0 for No): "); // promts for reset decision
    scanf("%d", &reset); // reads choice 

    if (reset == 1) { // check if user chose to reset sales
        total_amount = 0.0; //reset sales to zero
        printf("Sales reset successfully.\n"); // notifies user of change made
    } else {
        printf("Sales not reset.\n"); //notifies that sales were not reset
    }
}

// Function to display current ingredient quantities //
void display_ingredient_quantities() { //define function to display ingredient quantities
    printf("Coffee beans: %d g\n", coffee_beans); // display current coffee bean quantity
    printf("Water: %d ml\n", water); //display current quantity water
    printf("Milk: %d ml\n", milk); // display current quantity milk
    printf("Chocolate syrup: %d ml\n", chocolate_syrup); // display current quantity syrup
}