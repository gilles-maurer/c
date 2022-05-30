//By Gilles Maurer 
//Programming and Data Structure 
//Text Processing

#pragma once

//#ifndef __FUNCTIONS_H__
//#define __FUNCTIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* get_line();  

char* increaseLineBy1Character(char* line, int previousSize);

void inverse_text(char** new_str, int counter, char** str); 

char* inverse_line(char* line);

int get_previous_space(int i, char* line); 

void display_text(char** str, int counter);

void free_double_array(char** str, int counter);

void free_all(char** str, char** new_str, int counter);  

//#endif /* __FUNCTIONS_H__ */
