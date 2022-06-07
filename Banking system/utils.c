//By Gilles Maurer
//Programming and Data Structure
//Banking system

#include "utils.h"

void enter_name(char* name) {

    char temp[101];

    do {
        printf("Enter a name :");
        read_stdin(temp, 20);
    } while (!is_name_or_surname_correct(temp));

    strcpy(name, temp);
    printf("name :%s\n", name);
}

void enter_surname(char* surname) {

    char temp[101];

    do {
        printf("Enter a surname :");
        read_stdin(temp, 20);
    } while (!is_name_or_surname_correct(temp));

    strcpy(surname, temp);
    printf("surname :%s\n", surname);
}

void enter_adresse(char* adresse){

    char temp[101];

    do {
        printf("Enter an adresse :");
        read_stdin(temp, 100);
    } while (!is_adresse_correct(temp));

    strcpy(adresse, temp);
    printf("adresse :%s\n", adresse);

}

void enter_pesel(char* pesel){

    char temp[101];

    do {
        printf("Enter an identification number :");
        read_stdin(temp, 12);
    } while (!is_pesel_correct(temp));

    strcpy(pesel, temp);
    printf("pesel :%s\n", pesel);
}

void read_stdin(char temp[], int size){

    fgets(temp, size, stdin);

    if ((strlen(temp) > 0) && (temp[strlen(temp) - 1] == '\n')) {
        temp[strlen(temp) - 1] = '\0';
    } else {
        while(getchar() != '\n');
    }

}

bool is_name_or_surname_correct(char name[]) {

    int i = 0;
    bool result = true;

    while(name[i] != '\0' && result){
        if ((toupper(name[i]) < 'A' || toupper(name[i]) > 'Z') && name[i] != '-' && name[i] != ' '){
            result = false;
        }
        i++;
    }
    return result;
}

bool is_adresse_correct(char adresse[]) {

    int i = 0;
    bool result = true;

    while(adresse[i] != '\0' && result){
        if ((toupper(adresse[i]) < 'A' || toupper(adresse[i]) > 'Z') && adresse[i] != '-' && adresse[i] != ' '){
            if (adresse[i] < '0' || adresse[i] > '9') {
                result = false;
            }
        }
        i++;
    }
    return result;

}

bool is_pesel_correct(char pesel[]) {

    bool result = true;

    if (strlen(pesel) != 11) {
        result = false;
    }
    for (int i = 0; i < 11; ++i) {
        if (pesel[i] < '0' || pesel[i] > '9'){
            result = false;
        }
    }

    return result;
}

int scanf_and_clean_int(int* answer){
	
	int test; 
	test = scanf("%d", answer);
    while(getchar() != '\n');
    
    return test; 
    
}

int scanf_and_clean_char(char* answer){
	
	int test; 
	test = scanf("%c", answer);
    while(getchar() != '\n');
    
    return test; 
    
}

int scanf_and_clean_float(float* answer){
	
	int test; 
	test = scanf("%f", answer);
    while(getchar() != '\n');
    
    return test; 
}


int number_of_register_account(){

    FILE *file = open_file_in_reading_mode();

    fseek(file, 0, SEEK_END);
    long position = ftell(file);

    int account_number = (int)(position/sizeof(Customer));

    fclose(file);

    return account_number;
}

int select_account() {

    int answer;
    int test = scanf_and_clean_int(&answer);

    while (test != 1 || answer > number_of_register_account() || answer < 0){
        printf("Error, please enter it again : ");
        test = scanf_and_clean_int(&answer);
    }

    return answer;
}

float select_money() {

    float answer;
    int test = scanf_and_clean_float(&answer);

    while (test != 1 || answer < 0){
        printf("Error, please enter it again : ");
        test = scanf_and_clean_float(&answer);
    }

    return answer;
}

bool is_enough_money(int account, float money) {

    FILE *file = open_file_in_reading_mode();

    fseek(file, (long)sizeof(Customer) * (account-1), SEEK_SET);

    Customer customer;

    fread(&customer, sizeof(Customer), 1, file);

    fclose(file);

    if (customer.currentBalance >= money) {
        return true;
    } else {
        printf("Not enought money on the account, please enter it again\n");
        return false;
    }

}

void display_customer(Customer customer) {
    printf("Account %d : %s %s, adresse : %s, pesel : %s\nCurrent Balance : %.2f%c\n", customer.accountNumber,
           customer.surname, customer.name, customer.adresse, customer.pesel, customer.currentBalance, '$');
}


FILE* open_file_general(char* openMode){
	
	char fileName[] = "database.txt";
	FILE* file = fopen(fileName, openMode); 

	if (file == NULL) {
		printf("Error with the opening of the file\n");
		exit(0);
	}
	
	return file;
	
}

FILE* open_file_in_append_mode(){
	return open_file_general("ab");
}

FILE* open_file_in_reading_mode(){
	return open_file_general("rb");
}

FILE* open_file_in_reading_plus_mode(){
	return open_file_general("r+b");
}


void read_customer(FILE* file, int AccountNumber, Customer* customer){
	fseek(file, (long)sizeof(Customer) * (AccountNumber - 1), SEEK_SET);
	fread(customer, sizeof(Customer), 1, file);
}

void write_customer(FILE* file, int AccountNumber, Customer* customer){
	fseek(file, (long)sizeof(Customer) * (AccountNumber - 1), SEEK_SET);
	fwrite(customer, sizeof(Customer), 1, file);
}




