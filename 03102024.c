  #include <stdio.h>		// give access to the stdio.h library //


    //defining variables//

    #define admin_password "coffeemakersimulator"   //adminstrator password defined//

//PRICE//
    #define total_amount_espresso "3.5 AED"     // espresso price defined//
    #define total_amount_cappucino "4.5 AED"    //cappucino price defined//
    #define total_amount_mocha "5.5 AED"    // mocha price defined//

//BEANS//
    #define espresso_beans_grams 8    //espresso beans amount in grams defined//
    #define cappuccino_beans_grams 8    //cappuccino beans amount in grams defined//
    #define mocha_beans_grams 8         //mocha beans amoount in grams defined//

//WATER//
    #define espresso_water_millilitres 30   //espresso water amount in millilitres defined//
    #define cappuccino_water_millilitres 30     //cappuccino water amount in millilitres defined//
    #define mocha_water_millilitres 39  //mocha water amount in millilitres defined//

//MILK//
    #define espresso_milk_millilitres 0 //espresso milk amount in millilitres defined//
    #define cappuccino_milk_millilitres 70 //cappuccino milk amount in millilitres defined//
    #define mocha_milk_millilitres 160 //mocha milk amount in millilitres defined//

//SYRUP//
    #define espresso_syrup_millilitres 0 //espresso syrup amount in millilitres defined//
    #define cappuccino_syrup_millilitres 0 //cappuccino syrup amount in millilitres defined//
    #define mocha_syrup_millilitres 30 //mocha syrup amount in millilitres defined//

//LOW THRESHOLD//
    #define low_threshold_beans 240
    #define low_threshold_water 990
    #define low_threshold_milk 2300
    #define low_threshold_syrup 300


    //global functions//
    
    float initial_amount=0.0;

    float espresso_price=total_amount_espresso;
    float cappuccino_price=total_amount_cappucino;
    float mocha_price=total_amount_mocha;

    //function prototypes//
    void coffee_maker_simulator();
    void admin_mode();

int main(){

    #include<stdio.h>

int main() {
  int i;

  //infinite loop
  while (1){
    printf(" COFFEE MAKER SIMULATOR\n ");
    printf(" 1. ORDER A COFFEE\n ");
    printf(" 2. ADMIN MODE\n ");
    printf(" 3. EXIT\n ");
    scanf("%d", &i); //reads user's input//

    switch(i){
        case 1: 
        ******************************
        break;  // exit the loop
    else if (i<0)
       {
       printf(" you've inputted a negative value, I am going to skip the rest of the loop and branch back\n");       
       continue;  // skip the rest of the loop and go back to check the loop condition
       }
    else
       printf(" you've inputted the positive value %d\n", i);
  } // end of loop
} // end of main

}