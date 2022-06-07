//By Gilles Maurer
//Programming and Data Structure
//Banking system

#ifndef BANKING_SYSTEM_FUNCTIONS_H
#define BANKING_SYSTEM_FUNCTIONS_H

#include "utils.h"	

/****************Create account**************/

void create_a_new_account();

bool ask_confirmation_creation_account(Customer newCustomer);

/****************List account**************/

void list_all_accounts();


/****************Search account**************/

void search_for_an_account();

void search_by_account_number();

void search_by_name();

void search_by_surname();

void search_by_adress();

void search_by_pesel();

/****************transfer**************/

void make_a_money_transfer();

bool ask_confirmation_transfer(Customer customer1, Customer customer2, float money);

/******************deposit****************/

void make_a_deposit();

bool ask_confirmation_deposit(Customer customer, float money);

/******************withdrawal****************/

void make_a_withdrawal();

bool ask_confirmation_withdrawal(Customer customer, float money);

#endif //BANKING_SYSTEM_FUNCTIONS_H
