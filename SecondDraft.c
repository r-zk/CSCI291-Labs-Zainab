#include <stdio.h>

 //defining variables//
 #define admin_password 12345   //adminstrator password to access admin mode//

 //price in AED//
    #define total_amount_espresso 3.5      // espresso price//
    #define total_amount_cappucino 4.5    //cappucino price//
    #define total_amount_mocha 5.5    // mocha price//

//beans//
    #define espresso_beans_grams 8    //espresso beans amount in grams//
    #define cappuccino_beans_grams 8    //cappuccino beans amount in grams//
    #define mocha_beans_grams 8         //mocha beans amoount in grams//

//water//
    #define espresso_water_millilitres 30   //espresso water amount in millilitres//
    #define cappuccino_water_millilitres 30     //cappuccino water amount in millilitres//
    #define mocha_water_millilitres 39  //mocha water amount in millilitres//

//milk//
    #define espresso_milk_millilitres 0 //espresso milk amount in millilitres//
    #define cappuccino_milk_millilitres 70 //cappuccino milk amount in millilitres//
    #define mocha_milk_millilitres 160 //mocha milk amount in millilitres//

//syrup//
    #define espresso_syrup_millilitres 0 //espresso syrup amount in millilitres//
    #define cappuccino_syrup_millilitres 0 //cappuccino syrup amount in millilitres//
    #define mocha_syrup_millilitres 30 //mocha syrup amount in millilitres//

//low threshold//
    #define low_threshold_beans 50 //alert for beans//
    #define low_threshold_water 100 //alert for water//
    #define low_threshold_milk 150 //alert for milk//
    #define low_threshold_syrup 50 //alert for syrup//

    //global functions//
    float total_amount = 0.0;
    int coffee_beans = 240; // initial quantity beans
    int water = 990; // initial quantity beans
    int milk = 2300; // initial quantity beans
    int chocolate_syrup = 300 // initial quantity beans

// Function prototypes
;void make_espresso();
void make_cappuccino();
void make_mocha();
void check_ingredients();
void display_main_menu();
void admin_mode();
void process_payment(char *coffee_name, float price, int coffee_beans_required, int water_required, int milk_required, int chocolate_required);


// Main function
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
                printf("Exiting Simulator. ");
                return 0;
            default:
                printf("Error: Not an Option. \n");
        }
    }
    return 0;
}

// Functions definitions
void display_main_menu() {
    int coffee_choice;
    float price = 0.0;
    int confirmed = 0;
    int confirm_selection(char *coffee_name, float price);


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

// Function to confirm the user's selection
int confirm_selection(char *coffee_name, float price) {
    int confirmation;
    printf("You selected %s for %.2f AED. Confirm? (1 for Yes, 0 for No): ", coffee_name, price);
    scanf("%d", &confirmation);
    return confirmation == 1;
}

// Function to process the payment and update the ingredients
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

    // Update ingredients
    coffee_beans -= coffee_beans_required;
    water -= water_required;
    milk -= milk_required;
    chocolate_syrup -= chocolate_required;
    total_amount += price;

    // Check if any ingredient has fallen below the threshold
    check_ingredients();
}


void make_espresso() {
    if (coffee_beans >= espresso_beans_grams && water >= espresso_water_millilitres) {
        coffee_beans -= espresso_beans_grams;
        water -= espresso_water_millilitres;
        total_amount += total_amount_espresso;
        printf("Espresso Served. \n");
    } else {
        printf("Insufficient Ingredients\nUnable to Serve at this Time\n");
    }
}

void make_cappuccino() {
    if (coffee_beans >= cappuccino_beans_grams && water >= cappuccino_water_millilitres && milk >= cappuccino_milk_millilitres) {
        coffee_beans -= cappuccino_beans_grams;
        water -= cappuccino_water_millilitres;
        milk -= cappuccino_milk_millilitres;
        total_amount += total_amount_cappucino;
        printf("Cappuccino Served. \n");
    } else {
        printf("Insufficient Ingredients\nUnable to Serve at this Time\n");
    }
}

void make_mocha() {
    if (coffee_beans >= mocha_beans_grams && water >= mocha_water_millilitres && milk >= mocha_milk_millilitres && chocolate_syrup >= mocha_syrup_millilitres) {
        coffee_beans -= mocha_beans_grams;
        water -= mocha_water_millilitres;
        milk -= mocha_milk_millilitres;
        chocolate_syrup -= mocha_syrup_millilitres;
        total_amount += total_amount_mocha;
        printf("Mocha Served. \n");
    } else {
        printf("Insufficient Ingredients\nUnable to Serve at this Time\n");
    }
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

void admin_mode() {
    int password;
    printf("Enter admin password: ");
    scanf("%d", &password);
    if (password == admin_password) {
        //grant access
    } else {
        printf("Incorrect password.\n");
    }
}
