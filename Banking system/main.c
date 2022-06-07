//By Gilles Maurer
//Programming and Data Structure
//Banking system


#include "functions.h"


int main() {

    int rep = 0;

    while (rep != 7) {

        printf("\nHome Page :\nWhat do you want to do ?\n");
        printf("1 :  create a new account\n2 :  list all accounts\n");
        printf("3 :  search for an account\n4 :  make a money transfer\n");
        printf("5 :  make a deposit\n6 :  make a withdrawal\n7 : leave\n-->");
        scanf_and_clean_int(&rep);

        switch (rep) {
            case 1: create_a_new_account();
                break;
            case 2: list_all_accounts();
                break;
            case 3: search_for_an_account();
                break;
            case 4: make_a_money_transfer();
                break;
            case 5: make_a_deposit();
                break;
            case 6: make_a_withdrawal();
                break;
            default:
                break;
        }

    }

    return 0;
}
