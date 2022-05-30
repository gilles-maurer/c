//By Gilles Maurer 
//Programming and Data Structure 
//Text processing

#include "functions.h"


char* get_line() {
	
	char* line = NULL; 
	int counter = 0;
	
	char temp; 
	
	while((temp = getchar()) != EOF) {
		line = increaseLineBy1Character(line, counter);
		line[counter] = temp; 
		counter++;
		if (temp == '\n'){
			break;
		}
	}

	if (temp == EOF && counter == 0) {
		return NULL; 
	} 
	
	line = increaseLineBy1Character(line, counter);
	line[counter] = '\0';
	
	return line; 
}

char* increaseLineBy1Character(char* line, int previousSize){
	line = (char*) realloc(line, sizeof(char) * (previousSize + 1));	
	return line;
}


void inverse_text(char** new_str, int counter, char** str) {
	for (int i = 0; i < counter; i++) {	
		new_str[i] = inverse_line(str[i]);
	} 	
} 

char* inverse_line(char* line) {		
	
	char* newline = malloc(sizeof(char) * strlen(line)); 

	newline[0] = '\0';
	
	int i = strlen(line)-2; 
	
	while (i > 0) {
		int j = get_previous_space(i, line); 
	
		char word[i-j+1]; 
		
		for (int k = 0; k < (i-j-1); k++) {
			word[k] = line[j+1+k]; 
		}
		
		word[i-j-1] = ' ';
		word[i-j] = '\0';

		strcat(newline, word); 
		
		i = j; 	
	}
	
	newline[strlen(line)-2] = '\n';
	newline[strlen(line)-1] = '\0';

	return newline; 
}



int get_previous_space(int i, char* line) {
	
	int j = i-1; 

	while(j >= 0 && line[j] != ' ') {
		j--; 
	}	
	return j; 
}


void display_text(char** str, int counter){
	
	for (int i = 0; i < counter; i++) {
		printf("%s", str[i]); 		
	} 
}


void free_double_array(char** str, int counter) {
	
	for (int i = 0; i < counter; i++) {		
		free(str[i]); 		
	} 
}

void free_all(char** str, char** new_str, int counter) {
	
	free_double_array(str, counter);
	free(str); 
	free_double_array(new_str, counter); 
	
}







