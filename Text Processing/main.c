//By Gilles Maurer 
//Programming and Data Structure 
//Text processing

#include "functions.h"


int main() {
	
	char** str = NULL; 
	char* line; 
	
	int counter = 0; 

	while((line = get_line()) != NULL) {
		str = realloc(str, sizeof(char*) * (counter + 1));
		str[counter] = line;
		counter++; 
	}
	
	
	display_text(str, counter); 
	
	
	printf("-------------------Inverse sens-------------------\n");
		
		
	char* new_str[counter];
	inverse_text(new_str, counter, str); 
	display_text(new_str, counter); 
	
	
	free_all(str, new_str, counter);
	
	return 0;
}
