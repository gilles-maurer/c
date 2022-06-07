//By Gilles Maurer
//Programming and Data Structure
//Bsearch

#ifndef PDS_BSEARCH_FUNCTIONS_H
#define PDS_BSEARCH_FUNCTIONS_H

#include <stdio.h>
#include <string.h>

typedef struct {
	
	char name[20]; 
	char surname[20];
	int age; 
	
} Person; 


void* my_bsearch(const void* key, const void* base, size_t num, size_t size, int (*compar)(const void *, const void*));


void test_int(); 

void test_float(); 

void test_person();


void initialize_int_array(int* int_array); 

void initialize_float_array(float* float_array); 

void initialize_person_array(Person* person_array); 


int compare_int(const void * a, const void * b);

int compare_float(const void * a, const void * b);

int compare_person(const void * a, const void * b);


void result(void* item, int index); 
 

#endif //PDS_BSEARCH_FUNCTIONS_H
