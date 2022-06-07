//By Gilles Maurer
//Programming and Data Structure
//Banking system

#ifndef BANKING_SYSTEM_UTILS_H
#define BANKING_SYSTEM_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    int accountNumber;
    char name[20];
    char surname[20];
    char adresse[100];
    char pesel[12];
    float currentBalance;
} Customer;


void enter_name(char* name);

void enter_surname(char* surname);

void enter_adresse(char* adresse);

void enter_pesel(char* pesel);


void read_stdin(char temp[], int size);


bool is_name_or_surname_correct(char name[]);

bool is_adresse_correct(char adresse[]);

bool is_pesel_correct(char pesel[]);


int scanf_and_clean_int(int* answer); 

int scanf_and_clean_char(char* answer);

int scanf_and_clean_float(float* answer);


int number_of_register_account();

int select_account();

float select_money();

bool is_enough_money(int account, float money);

void display_customer(Customer customer);


FILE* open_file_general(char* openMode);

FILE* open_file_in_append_mode();

FILE* open_file_in_reading_mode();

FILE* open_file_in_reading_plus_mode();


void read_customer(FILE* file, int AccountNumber, Customer*customer); 

void write_customer(FILE* file, int AccountNumber, Customer* customer); 

#endif //BANKING_SYSTEM_UTILS_H

