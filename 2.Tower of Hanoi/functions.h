// By Gilles Maurer
// Programming and Data Structure
// Tower of Hanoi

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "primlib.h"

#define NUMBER_OF_PEGS 3
#define NUMBER_OF_DISC 7

#define HEIGHT_OF_GROUND 50
#define LEFT_PEG_X (gfx_screenWidth() / (NUMBER_OF_PEGS + 1))
#define SPACE_BETWEEN_PEG (gfx_screenWidth() / (NUMBER_OF_PEGS + 1))
#define WIDTH_OF_PEG 20
#define HEIGHT_OF_PEG 400

#define HEIGHT_OF_DISC (HEIGHT_OF_PEG / (NUMBER_OF_DISC + 1))
#define MAX_WIDTH_DISC (SPACE_BETWEEN_PEG - WIDTH_OF_PEG)
#define MIN_WIDTH_DISC (2 * WIDTH_OF_PEG)
#define DISC_INTERVAL_WIDTH                                                    \
	((MAX_WIDTH_DISC - MIN_WIDTH_DISC) / (NUMBER_OF_DISC - 1))

#define MAX_HEIGHT_ANIMATION (gfx_screenHeight() * 1 / 8)
#define ANIMATION_SPEED 5

typedef struct {
	int numberOfDisc;
	float width;
	int positionOnPeg;
	int numberOfPeg;
} Disc;

typedef struct {
	int startingPeg;
	int endingPeg;
} Instruction;

void draw_background();

void draw_number_peg(int peg);

void initialize_discs(Disc discArray[NUMBER_OF_DISC]);

void draw_all_discs(Disc discArray[NUMBER_OF_DISC]);

void draw_all_discs_except_one(Disc discArray[NUMBER_OF_DISC],
							   int numberOfException);

float x_position_of_peg(int pegNumber);

void draw_disc(Disc disc, float xShift, float yShift);

void draw_background_and_discs(Disc discArray[NUMBER_OF_DISC]);

int highter_position_on_peg(int pegNumber, Disc discArray[NUMBER_OF_DISC]);

Disc highter_disc_on_peg(int pegNumber, Disc discArray[NUMBER_OF_DISC]);

Instruction get_instruction();

bool is_instruction_valid(Instruction instruction,
						  Disc discArray[NUMBER_OF_DISC]);

void move_disc(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC]);

void animation_rise(Disc discArray[NUMBER_OF_DISC], Disc animatedDisc);

void animation_x(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC],
				 Disc animatedDisc);

void animation_x_right_to_left(int startPeg, int endPeg,
							   Disc discArray[NUMBER_OF_DISC],
							   Disc animatedDisc);

void animation_x_left_to_right(int startPeg, int endPeg,
							   Disc discArray[NUMBER_OF_DISC],
							   Disc animatedDisc);

void animation_drop(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC],
					Disc animatedDisc);

void update_disc(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC]);

bool check_win(Disc discArray[NUMBER_OF_DISC]);

void win_display();

#endif /* __FUNCTIONS_H__ */
