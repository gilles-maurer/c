// By Gilles Maurer
// Programming and Data Structure
// Tower of Hanoi

#include "functions.h"

int main(int argc, char* argv[]) {
	if (gfx_init()) {
		exit(3);
	}

	Disc discArray[NUMBER_OF_DISC];

	initialize_discs(discArray);
	draw_background_and_discs(discArray);
	gfx_updateScreen();

	while (!check_win(discArray)) {

		Instruction instruction = get_instruction();

		if (is_instruction_valid(instruction, discArray)) {

			move_disc(instruction.startingPeg, instruction.endingPeg,
					  discArray);
			update_disc(instruction.startingPeg, instruction.endingPeg,
						discArray);
			draw_background_and_discs(discArray);
			gfx_updateScreen();
		}
	}

	win_display();

	return 0;
}
