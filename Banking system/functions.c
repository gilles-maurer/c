// By Gilles Maurer
// Programming and Data Structure
// Banking system

#include "functions.h"

/****************Create account**************/

void create_a_new_account() {

	Customer newCustomer;

	printf("Create a new account\n");

	enter_name(newCustomer.name);

	enter_surname(newCustomer.surname);

	enter_adresse(newCustomer.adresse);

	enter_pesel(newCustomer.pesel);

	newCustomer.currentBalance = 0;
	newCustomer.accountNumber = number_of_register_account() + 1;

	if (ask_confirmation_creation_account(newCustomer)) {

		FILE* file = open_file_in_append_mode();
		fwrite(&newCustomer, sizeof(Customer), 1, file);
		fclose(file);
	}
}

bool ask_confirmation_creation_account(Customer newCustomer) {

	char answer;

	printf("---Do you want to create an account for %s %s ?---\n",
		   newCustomer.surname, newCustomer.name);
	printf("---Adresse : %s, pesel : %s---\n", newCustomer.adresse,
		   newCustomer.pesel);
	printf("---Account number : %d---\n", newCustomer.accountNumber);
	do {
		printf("Y/N : ");
		scanf_and_clean_char(&answer);
	} while (toupper(answer) != 'Y' && toupper(answer) != 'N');

	if (toupper(answer) == 'Y') {
		return true;
	} else {
		return false;
	}
}

/****************List account**************/

void list_all_accounts() {

	if (number_of_register_account() == 0) {
		printf("\nNo account register\n\n");
	} else {

		FILE* file = open_file_in_reading_mode();

		Customer customer;

		printf("\n");
		while (fread(&customer, sizeof(Customer), 1, file) != 0) {
			display_customer(customer);
		}
		printf("\n");
		fclose(file);
	}
}

/****************Search account**************/

void search_for_an_account() {

	int rep;
	bool out;

	do {
		out = true;
		printf("\nSearch account :\nWhich field do you want to search ?\n");
		printf("1 :  account number\n2 :  name\n");
		printf("3 :  surname\n4 :  adress\n");
		printf("5 :  pesel\n-->");
		scanf_and_clean_int(&rep);

		switch (rep) {
		case 1:
			search_by_account_number();
			break;
		case 2:
			search_by_name();
			break;
		case 3:
			search_by_surname();
			break;
		case 4:
			search_by_adress();
			break;
		case 5:
			search_by_pesel();
			break;
		default:
			printf("Error, enter it again\n");
			out = false;
			break;
		}
	} while (!out);
}

void search_by_account_number() {

	printf("Enter a account number : ");
	int accountNumber = select_account();

	FILE* file = open_file_in_reading_mode();

	Customer customer;
	printf("\n");
	while (fread(&customer, sizeof(Customer), 1, file) != 0) {
		if (accountNumber == customer.accountNumber) {
			display_customer(customer);
		}
	}
	printf("\n");
	fclose(file);
}

void search_by_name() {

	char name[20];

	enter_name(name);

	FILE* file = open_file_in_reading_mode();

	Customer customer;
	bool empty = true;
	printf("\n");
	while (fread(&customer, sizeof(Customer), 1, file) != 0) {
		if (strcmp(customer.name, name) == 0) {
			display_customer(customer);
			empty = false;
		}
	}

	if (empty) {
		printf("This name is not in the database");
	}

	printf("\n");
	fclose(file);
}

void search_by_surname() {

	char surname[20];

	enter_surname(surname);

	FILE* file = open_file_in_reading_mode();

	Customer customer;
	bool empty = true;
	printf("\n");
	while (fread(&customer, sizeof(Customer), 1, file) != 0) {
		if (strcmp(customer.surname, surname) == 0) {
			display_customer(customer);
			empty = false;
		}
	}

	if (empty) {
		printf("This surname is not in the database");
	}

	printf("\n");
	fclose(file);
}

void search_by_adress() {

	char adresse[100];

	enter_adresse(adresse);

	FILE* file = open_file_in_reading_mode();

	Customer customer;
	bool empty = true;
	printf("\n");
	while (fread(&customer, sizeof(Customer), 1, file) != 0) {
		if (strcmp(customer.adresse, adresse) == 0) {
			display_customer(customer);
			empty = false;
		}
	}

	if (empty) {
		printf("This adresse is not in the database");
	}

	printf("\n");
	fclose(file);
}

void search_by_pesel() {

	char pesel[12];

	enter_pesel(pesel);

	FILE* file = open_file_in_reading_mode();

	Customer customer;
	bool empty = true;
	printf("\n");
	while (fread(&customer, sizeof(Customer), 1, file) != 0) {
		if (strcmp(customer.pesel, pesel) == 0) {
			display_customer(customer);
			empty = false;
		}
	}

	if (empty) {
		printf("This identification number is not in the database");
	}

	printf("\n");
	fclose(file);
}

/****************transfer**************/

void make_a_money_transfer() {

	int number_account1, number_account2;
	float money;

	do {

		printf("Enter the number of the account you want to take the money "
			   "from : ");
		number_account1 = select_account();

		printf(
			"Enter the number of the account you want to put the money on : ");
		number_account2 = select_account();

		printf("How many money do you want to transfer : ");
		money = select_money();

	} while (!is_enough_money(number_account1, money));

	FILE* file = open_file_in_reading_plus_mode();

	Customer account1, account2;

	read_customer(file, number_account1, &account1); 
	read_customer(file, number_account2, &account2); 


	if (ask_confirmation_transfer(account1, account2, money)) {
		account1.currentBalance = account1.currentBalance - money;
		account2.currentBalance = account2.currentBalance + money;
		
		write_customer(file, number_account1, &account1); 
		write_customer(file, number_account2, &account2); 
		
	}

	fclose(file);
}

bool ask_confirmation_transfer(Customer customer1, Customer customer2,
							   float money) {

	char answer;

	printf("---Do you want to transfer %.2f%c---\n", money, '$');
	printf("---From the account of %s %s---\n", customer1.surname,
		   customer1.name);
	printf("---To the account of %s %s---\n", customer2.surname,
		   customer2.name);
	do {
		printf("Y/N : ");
		scanf_and_clean_char(&answer);
	} while (toupper(answer) != 'Y' && toupper(answer) != 'N');

	if (toupper(answer) == 'Y') {
		return true;
	} else {
		return false;
	}
}

/****************deposit**************/

void make_a_deposit() {
	int number_account;
	float money;

	printf(
		"Enter the number of the account you want to deposit the money on : ");
	number_account = select_account();
	printf("How many money do you want to deposit : ");
	money = select_money();

	FILE* file = open_file_in_reading_plus_mode();

	Customer account;
	
	read_customer(file, number_account, &account); 

	if (ask_confirmation_deposit(account, money)) {
		account.currentBalance = account.currentBalance + money;
		
		write_customer(file, number_account, &account);
	}

	fclose(file);
}

bool ask_confirmation_deposit(Customer customer, float money) {

	char answer;

	printf("---Do you want to deposit %.2f%c---\n", money, '$');
	printf("---On the account of %s %s---\n", customer.surname, customer.name);
	do {
		printf("Y/N : ");
		scanf_and_clean_char(&answer);
	} while (toupper(answer) != 'Y' && toupper(answer) != 'N');

	if (toupper(answer) == 'Y') {
		return true;
	} else {
		return false;
	}
}

/****************withdrawal**************/

void make_a_withdrawal() {
	int number_account;
	float money;

	do {
		printf("Enter the number of the account you want to withdrawal the "
			   "money from : ");
		number_account = select_account();
		printf("How many money do you want to withdrawal : ");
		money = select_money();
	} while (!is_enough_money(number_account, money));

	FILE* file = open_file_in_reading_plus_mode();

	Customer account;

	read_customer(file, number_account, &account); 

	if (ask_confirmation_withdrawal(account, money)) {
		account.currentBalance = account.currentBalance - money;

		write_customer(file, number_account, &account);
	}

	fclose(file);
}

bool ask_confirmation_withdrawal(Customer customer, float money) {

	char answer;

	printf("---Do you want to withdrawal %.2f%c---\n", money, '$');
	printf("---From the account of %s %s---\n", customer.surname,
		   customer.name);
	do {
		printf("Y/N : ");
		scanf_and_clean_char(&answer);
	} while (toupper(answer) != 'Y' && toupper(answer) != 'N');

	if (toupper(answer) == 'Y') {
		return true;
	} else {
		return false;
	}
}
