//By Gilles Maurer 
//Programming and Data Structure 
//Tetris

#include "functions.h"


int main(int argc, char* argv[]) {
	
	if (gfx_init()) {
		exit(3);
	}
	
	initialize_global_variables();
	
	Piece piece = pull_next_piece(); 
	
	do {	
		
		Piece nextPiece = pull_next_piece(); 
		
		while (!is_piece_down(piece)) {
			print_piece(piece); 
			update_screen(nextPiece);
			change_type_piece(piece, EMPTY);
			SDL_Delay(falling_piece_animation_delay);
			piece.center.y++; 
			piece = instruction_loop(piece, nextPiece); 
			
		}
		
		change_type_piece(piece, GROUND);
		update_screen(nextPiece);
		check_all_line(); 
		update_screen(nextPiece);
		
		piece = nextPiece; 
		falling_piece_animation_delay = delayOfFall;	
		clean_memory_command();
		
	} while (!check_lose(piece)); 


	lose_display(); 

	
	return 0;
}

