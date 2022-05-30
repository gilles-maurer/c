//By Gilles Maurer 
//Programming and Data Structure 
//Tetris


#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "primlib.h"

#include "piece_definition.h"


#define HEIGHT_OF_GAME_FIELD 20
#define WIDTH_OF_GAME_FIELD 10
#define SIZE_OF_UNIT_SQUARE (600 / HEIGHT_OF_GAME_FIELD)

#define FIRST_DELAY_OF_FALL 250
#define LAST_DELAY_OF_FALL 60
#define MAX_SPEED_SCORE 50
#define INTERVAL_DELAY_OF_FALL ((FIRST_DELAY_OF_FALL - LAST_DELAY_OF_FALL) / MAX_SPEED_SCORE)


int gameField[WIDTH_OF_GAME_FIELD][HEIGHT_OF_GAME_FIELD];
int score; 
int delayOfFall;
int falling_piece_animation_delay;
 

typedef struct {
	
	int x; 
	int y; 
	
} Point; 

typedef struct {
	
	Point center;
	int kind; 
	int rotation; 
		
} Piece; 


enum instruction { MOVE_RIGHT, MOVE_LEFT, ROTATION, MOVE_DOWN, NO_INSTRUCTION };

enum squareFieldType {EMPTY, PIECE, CENTER_OF_PIECE, GROUND }; 

/****************************INITIALISATION****************************/

void initialize_global_variables();

/*******************************DISPLAY********************************/

void update_screen(Piece nextPiece); 

void print_background();

void display_game_field(); 

enum color color_of_square(int numSquare); 

void display_next_piece(int piece);

void display_score(); 

void lose_display(); 

void convert_score_in_string(char scoreString[4]); 

void print_piece(Piece piece);


/****************************INSTRUCTIONS******************************/

enum instruction get_instruction(); 

Piece instruction_loop(Piece piece, Piece nextPiece);

Piece apply_instruction(Piece piece, enum instruction newInstruction);

void clean_memory_command(); 


/**************************ACTION ON PIECES****************************/

Point find_center_piece(int pieceNumber, int rotation);

void change_type_piece(Piece piece, enum squareFieldType type);

Piece pull_next_piece(); 


/**************************ACTION ON LINES*****************************/

void check_all_line(); 

void deplace_lines(int startingLine); 


/****************************BOOL CHECK********************************/

bool is_piece_down(Piece piece);

bool check_exceed_game_field_and_overlapping(Piece potentialPiece); 

bool check_complete_line(int numberLine); 

bool check_lose(Piece piece); 



#endif /* __FUNCTIONS_H__ */
