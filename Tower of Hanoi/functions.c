// By Gilles Maurer
// Programming and Data Structure
// Tower of Hanoi

#include "functions.h"

void draw_background() {

	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);

	gfx_filledRect(0, gfx_screenHeight() - HEIGHT_OF_GROUND + 1,
				   gfx_screenWidth(), gfx_screenHeight(), YELLOW);

	for (int i = 1; i <= NUMBER_OF_PEGS; i++) {
		gfx_filledRect(x_position_of_peg(i) - (WIDTH_OF_PEG / 2),
					   gfx_screenHeight() - (HEIGHT_OF_PEG + HEIGHT_OF_GROUND),
					   x_position_of_peg(i) + (WIDTH_OF_PEG / 2),
					   gfx_screenHeight() - HEIGHT_OF_GROUND, RED);

		draw_number_peg(i);
	}
}

void draw_number_peg(int peg) {

	char string[2];
	string[0] = '0' + peg - 1;
	string[1] = '\0';
	gfx_textout(x_position_of_peg(peg),
				gfx_screenHeight() - (HEIGHT_OF_GROUND / 2), string, BLACK);
}

void initialize_discs(Disc discArray[NUMBER_OF_DISC]) {

	for (int i = 0; i < NUMBER_OF_DISC; i++) {
		discArray[i].numberOfDisc = i + 1;
		discArray[i].numberOfPeg = 1;
		discArray[i].positionOnPeg = i + 1;
		discArray[i].width =
			MIN_WIDTH_DISC + (DISC_INTERVAL_WIDTH * (NUMBER_OF_DISC - 1 - i));
	}
}

void draw_all_discs(Disc discArray[NUMBER_OF_DISC]) {

	for (int i = 0; i < NUMBER_OF_DISC; i++) {
		draw_disc(discArray[i], 0, 0);
	}
}

void draw_all_discs_except_one(Disc discArray[NUMBER_OF_DISC],
							   int numberOfException) {

	for (int i = 0; i < NUMBER_OF_DISC; i++) {
		if (discArray[i].numberOfDisc != numberOfException) {
			draw_disc(discArray[i], 0, 0);
		}
	}
}

float x_position_of_peg(int pegNumber) {

	float position;

	position = ((pegNumber - 1) * SPACE_BETWEEN_PEG) + LEFT_PEG_X;

	return position;
}

void draw_disc(Disc disc, float xShift, float yShift) {

	gfx_filledRect(
		x_position_of_peg(disc.numberOfPeg) - (disc.width / 2) + xShift,
		gfx_screenHeight() - HEIGHT_OF_GROUND -
			(disc.positionOnPeg * HEIGHT_OF_DISC) - yShift,
		x_position_of_peg(disc.numberOfPeg) + (disc.width / 2) + xShift,
		gfx_screenHeight() - HEIGHT_OF_GROUND -
			((disc.positionOnPeg - 1) * HEIGHT_OF_DISC) - yShift,
		BLUE);

	gfx_rect(x_position_of_peg(disc.numberOfPeg) - (disc.width / 2) + xShift,
			 gfx_screenHeight() - HEIGHT_OF_GROUND -
				 (disc.positionOnPeg * HEIGHT_OF_DISC) - yShift,
			 x_position_of_peg(disc.numberOfPeg) + (disc.width / 2) + xShift,
			 gfx_screenHeight() - HEIGHT_OF_GROUND -
				 ((disc.positionOnPeg - 1) * HEIGHT_OF_DISC) - yShift,
			 CYAN);
}

void draw_background_and_discs(Disc discArray[NUMBER_OF_DISC]) {

	draw_background();
	draw_all_discs(discArray);
}

int highter_position_on_peg(int pegNumber, Disc discArray[NUMBER_OF_DISC]) {

	int i = NUMBER_OF_DISC;
	int position = 0;

	do {
		if (discArray[i].numberOfPeg == pegNumber) {
			position = discArray[i].positionOnPeg;
		}
		i = i - 1;
	} while ((i >= 0) && (position == 0));

	return position;
}

Disc highter_disc_on_peg(int pegNumber, Disc discArray[NUMBER_OF_DISC]) {

	int i = NUMBER_OF_DISC;

	do {
		if (discArray[i].numberOfPeg == pegNumber) {
			break;
		}
		i = i - 1;
	} while (i >= 0);

	return discArray[i];
}

Instruction get_instruction() {

	Instruction instruction;
	int key1, key2;

	do {
		key1 = gfx_getkey();
		key2 = gfx_getkey();
	} while ((key1 < '0') || (key1 >= '0' + NUMBER_OF_PEGS) || (key2 < '0') ||
			 (key2 >= '0' + NUMBER_OF_PEGS) || (key1 == key2));

	instruction.startingPeg = key1 - '0' + 1;
	instruction.endingPeg = key2 - '0' + 1;

	return instruction;
}

bool is_instruction_valid(Instruction instruction,
						  Disc discArray[NUMBER_OF_DISC]) {

	if (highter_position_on_peg(instruction.startingPeg, discArray) == 0) {
		return false;
	}
	if (highter_position_on_peg(instruction.endingPeg, discArray) == 0) {
		return true;
	}
	if (highter_disc_on_peg(instruction.startingPeg, discArray).numberOfDisc >
		highter_disc_on_peg(instruction.endingPeg, discArray).numberOfDisc) {
		return true;
	}
	return false;
}

void move_disc(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC]) {

	Disc animatedDisc = highter_disc_on_peg(startPeg, discArray);

	animation_rise(discArray, animatedDisc);
	animation_x(startPeg, endPeg, discArray, animatedDisc);
	animation_drop(startPeg, endPeg, discArray, animatedDisc);
}

void animation_rise(Disc discArray[NUMBER_OF_DISC], Disc animatedDisc) {

	for (int y = 0; y < gfx_screenHeight() - HEIGHT_OF_GROUND -
							(animatedDisc.positionOnPeg * HEIGHT_OF_DISC) -
							MAX_HEIGHT_ANIMATION;
		 y = y + 1) {
		draw_background();
		draw_all_discs_except_one(discArray, animatedDisc.numberOfDisc);
		draw_disc(animatedDisc, 0, y);
		gfx_updateScreen();
		SDL_Delay(ANIMATION_SPEED);
	}
}

void animation_x(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC],
				 Disc animatedDisc) {

	if (startPeg > endPeg) {
		animation_x_right_to_left(startPeg, endPeg, discArray, animatedDisc);
	} else {
		animation_x_left_to_right(startPeg, endPeg, discArray, animatedDisc);
	}
}

void animation_x_right_to_left(int startPeg, int endPeg,
							   Disc discArray[NUMBER_OF_DISC],
							   Disc animatedDisc) {

	for (int x = 0; x > (SPACE_BETWEEN_PEG * (endPeg - startPeg)); x = x - 1) {
		draw_background();
		draw_all_discs_except_one(discArray, animatedDisc.numberOfDisc);
		draw_disc(animatedDisc, x,
				  gfx_screenHeight() - HEIGHT_OF_GROUND -
					  (animatedDisc.positionOnPeg * HEIGHT_OF_DISC) -
					  MAX_HEIGHT_ANIMATION);
		gfx_updateScreen();
		SDL_Delay(ANIMATION_SPEED);
	}
}

void animation_x_left_to_right(int startPeg, int endPeg,
							   Disc discArray[NUMBER_OF_DISC],
							   Disc animatedDisc) {

	for (int x = 0; x < (SPACE_BETWEEN_PEG * (endPeg - startPeg)); x = x + 1) {
		draw_background();
		draw_all_discs_except_one(discArray, animatedDisc.numberOfDisc);
		draw_disc(animatedDisc, x,
				  gfx_screenHeight() - HEIGHT_OF_GROUND -
					  (animatedDisc.positionOnPeg * HEIGHT_OF_DISC) -
					  MAX_HEIGHT_ANIMATION);
		gfx_updateScreen();
		SDL_Delay(ANIMATION_SPEED);
	}
}

void animation_drop(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC],
					Disc animatedDisc) {

	for (int y = gfx_screenHeight() - HEIGHT_OF_GROUND -
				 (animatedDisc.positionOnPeg * HEIGHT_OF_DISC) -
				 MAX_HEIGHT_ANIMATION;
		 y > (highter_position_on_peg(endPeg, discArray) -
			  highter_position_on_peg(startPeg, discArray) + 1) *
				 HEIGHT_OF_DISC;
		 y = y - 1) {
		draw_background();
		draw_all_discs_except_one(discArray, animatedDisc.numberOfDisc);
		draw_disc(animatedDisc, SPACE_BETWEEN_PEG * (endPeg - startPeg), y);
		gfx_updateScreen();
		SDL_Delay(ANIMATION_SPEED);
	}
}

void update_disc(int startPeg, int endPeg, Disc discArray[NUMBER_OF_DISC]) {

	int numberMovingDisc =
		highter_disc_on_peg(startPeg, discArray).numberOfDisc;
	discArray[numberMovingDisc - 1].positionOnPeg =
		highter_position_on_peg(endPeg, discArray) + 1;
	discArray[numberMovingDisc - 1].numberOfPeg = endPeg;
}

bool check_win(Disc discArray[NUMBER_OF_DISC]) {

	for (int i = 2; i <= NUMBER_OF_PEGS; i++) {
		if (highter_position_on_peg(i, discArray) == NUMBER_OF_DISC) {
			return true;
		}
	}
	return false;
}

void win_display() {
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	gfx_textout((gfx_screenWidth() / 2) - 100, gfx_screenHeight() / 2,
				"CONGRATULATION, YOU WIN !!!", RED);
	gfx_updateScreen();
	gfx_getkey();
}
