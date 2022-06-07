//By Gilles Maurer
//Programming and Data Structure
//Bsearch

#include "functions.h"


void* my_bsearch(const void* key, const void* base, size_t num, size_t size, int (*compar)(const void *, const void*)) {

    size_t left = 0;
    size_t right = num - 1;

    while (left <= right) {
				
        size_t mid = left + ((right - left) / 2);

        int cmp = (*compar)((char*)base + (mid * size), key);
                        
        if (cmp == 0) {
            return (char*)base + (mid * size); 
        } else if (cmp > 0) {
			
			if (mid > 1) {
				right = mid - 1;
			} else {
				break;
			}
			
        } else {
            left = mid + 1;
        }
    }
    return NULL;

}


void test_int() {

	printf("TEST INT\n");

	int array[100];
	initialize_int_array(array);
	
	int* item;
	int key = 52;
	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));
	
	
	key = 0;	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));
	
	key = 101;	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));
	
	key = 198;	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));

	key = -5;	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));
	
	key = 200;	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));
	
	
	
	
	
	key = 234;
	
	item = (int*)my_bsearch(&key, array, 100, sizeof(int), &compare_int);
	result(item, (int)(item - array));

}

void test_float(){
	
	printf("\nTEST FLOAT\n");

	float array[100];
	initialize_float_array(array);
	
	float* item; 
	float key = 82.8; 

	item = (float*)my_bsearch(&key, array, 100, sizeof(float), &compare_float); 
	result(item, (int)(item - array));
 
	key = 55.5;
	
	item = (float*)my_bsearch(&key, array, 100, sizeof(float), &compare_float); 
	result(item, (int)(item - array));
    
}

void test_person(){
	
	printf("\nTEST STRUCTURE\n");
	
	Person array[5]; 
	initialize_person_array(array);
	
	Person* item; 
	Person key; 
	
	strcpy(key.name, "thomas"); 
	strcpy(key.surname, "louis"); 
	key.age = 34; 
	
	item = (Person*)my_bsearch(&key, array, 5, sizeof(Person), &compare_person); 
	result(item, (int)(item - array));

    strcpy(key.name, "dupont"); 
	strcpy(key.surname, "gilles"); 
	key.age = 56; 
	
	item = (Person*)my_bsearch(&key, array, 5, sizeof(Person), &compare_person); 
	result(item, (int)(item - array));
}

void initialize_int_array(int* int_array) {
	
	for (int i = 0; i < 100; i++) {
		int_array[i] = 2*i; 
	}
}

void initialize_float_array(float* float_array){
	
	for (int i = 0; i < 100; i++) {
		float_array[i] = 1.2 * i; 
	}
}

void initialize_person_array(Person* person_array){
	
	char* name_array[5] = {"maurer", "martin", "bernard", "thomas", "petit"};
	char* surname_array[5] = {"arthur", "gabriel", "leo", "louis", "raphael"};
	int age_array[5] = {18, 19, 52, 34, 11};
	
	for (int i = 0; i < 5; i++) {
		
		Person newPerson; 
		strcpy(newPerson.name, name_array[i]); 
		strcpy(newPerson.surname, surname_array[i]); 
		newPerson.age = age_array[i]; 
		
		person_array[i] = newPerson; 	
	}	
}


int compare_int(const void * a, const void * b) {

    int *val1, *val2;
    val1 = (int*)a;
    val2 = (int*)b;

    return (*val1 - *val2);
}


int compare_float(const void * a, const void * b){

    float *val1, *val2;
    val1 = (float*)a;
    val2 = (float *)b;
    
    float cmp = *val1 - *val2; 
    
    if (cmp == 0) {
		return 0;
	} else if (cmp < 0){
		return -1; 
	} else {
		return 1;
	}
    
}

int compare_person(const void * a, const void * b){

	Person *val1, *val2; 
	val1 = (Person*)a;
    val2 = (Person *)b;

    return strcmp(val1->surname, val2->surname);
}


void result(void* item, int index) {
	
	if (item != NULL) {
		printf("Found item at the index : %d\n", index);
	} else {
		printf("Item could not be found\n");
	}
}








 
