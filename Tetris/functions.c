//By Gilles Maurer 
//Programming and Data Structure 
//Tetris

#include "functions.h"


/****************************INITIALISATION****************************/

void initialize_global_variables() {
	
	srand(time(0)); 
	
	for (int i = 0; i < WIDTH_OF_GAME_FIELD; i++) {
		for (int j = 0; j < HEIGHT_OF_GAME_FIELD; j++) {
				gameField[i][j] = EMPTY; 
		}
	}
	
	score = 0; 
	delayOfFall = FIRST_DELAY_OF_FALL; 
	falling_piece_animation_delay = delayOfFall;	
	
}


/*******************************DISPLAY********************************/

void update_screen(Piece nextPiece) {
	
	print_background();
	display_game_field(gameField); 
	display_next_piece(nextPiece.kind); 
	display_score();
	
	gfx_updateScreen();
	
}

void print_background() {
	
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	
}

void display_game_field() {
	
	Point gameFieldOrigin; 

	gameFieldOrigin.x = (gfx_screenWidth() / 2) - ((WIDTH_OF_GAME_FIELD*SIZE_OF_UNIT_SQUARE)/2); 
	gameFieldOrigin.y = gfx_screenHeight() - (HEIGHT_OF_GAME_FIELD * SIZE_OF_UNIT_SQUARE); 
	
	for (int i = 0; i < WIDTH_OF_GAME_FIELD; i++) {
		
		for (int j = 0;	j < HEIGHT_OF_GAME_FIELD; j++) {
			
			gfx_filledRect(gameFieldOrigin.x + (i * SIZE_OF_UNIT_SQUARE), gameFieldOrigin.y + (j * SIZE_OF_UNIT_SQUARE) , 
			gameFieldOrigin.x + ((i + 1) * SIZE_OF_UNIT_SQUARE), gameFieldOrigin.y + ((j + 1) * SIZE_OF_UNIT_SQUARE), 
			color_of_square(gameField[i][j])); 
			
			gfx_rect(gameFieldOrigin.x + (i * SIZE_OF_UNIT_SQUARE), gameFieldOrigin.y + (j * SIZE_OF_UNIT_SQUARE) , 
			gameFieldOrigin.x + ((i + 1) * SIZE_OF_UNIT_SQUARE), gameFieldOrigin.y + ((j + 1) * SIZE_OF_UNIT_SQUARE), CYAN); 
			
		}
	}
}

enum color color_of_square(int numSquare) {
	
	switch (numSquare) {
		case EMPTY: return BLACK; 
			break; 
		case PIECE: return GREEN; 
			break; 
		case CENTER_OF_PIECE: return YELLOW; 
			break; 
		case GROUND: return RED; 
			break; 		
		default: return MAGENTA; 	
	}
	
}

void display_next_piece(int piece) {
	
	Point nextPieceOrigin; 

	nextPieceOrigin.x = (3 * gfx_screenWidth()) / 4; 
	nextPieceOrigin.y = gfx_screenHeight() / 4; 
	
	for (int i = 0; i < 4; i++) {
		
		for (int j = 0;	j < 4; j++) {
			
			gfx_filledRect(nextPieceOrigin.x + (i * SIZE_OF_UNIT_SQUARE), nextPieceOrigin.y + (j * SIZE_OF_UNIT_SQUARE) , 
			nextPieceOrigin.x + ((i + 1) * SIZE_OF_UNIT_SQUARE), nextPieceOrigin.y + ((j + 1) * SIZE_OF_UNIT_SQUARE), 
			color_of_square(pieceDefinition[piece][0][i][j])); 
			
		}
	}
	
}

void display_score() { 
	
	char scoreString[4];
	
	convert_score_in_string(scoreString); 
	
	gfx_textout(gfx_screenWidth() / 5, gfx_screenHeight() / 5, scoreString, RED); 
	
}

void lose_display() {
	
	char scoreString[4]; 
	convert_score_in_string(scoreString); 	
	
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	gfx_textout((gfx_screenWidth() / 2) - 50, gfx_screenHeight() / 2, "GAME OVER", RED); 
	gfx_textout((gfx_screenWidth() / 2) - 25, gfx_screenHeight() / 2 + 20, scoreString, RED); 
	gfx_updateScreen();
	gfx_getkey();
}

void convert_score_in_string(char scoreString[4]) {
	
	int one, ten, hundred; 
	
	one = score % 10; 
	ten = ((score - one) % 100) / 10; 
	hundred = (score - ten - one) / 100; 
	
	scoreString[0] = hundred + '0'; 
	scoreString[1] = ten + '0'; 
	scoreString[2] = one + '0'; 
	scoreString[3] = '\0'; 
}

void print_piece(Piece piece) {
	
	Point centerPiece = find_center_piece(piece.kind, piece.rotation); 
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieceDefinition[piece.kind][piece.rotation][i][j] != 0) {
				gameField[i + piece.center.x - centerPiece.x][j + piece.center.y - centerPiece.y] = pieceDefinition[piece.kind][piece.rotation][i][j]; 
			}
		}
	}
}


/****************************INSTRUCTIONS******************************/

enum instruction get_instruction() {
	
	enum instruction newInstruction; 
	int key = gfx_pollkey(); 
	
	switch (key) {
		case SDLK_RIGHT: newInstruction = MOVE_RIGHT; 
			break; 
		case SDLK_LEFT: newInstruction = MOVE_LEFT; 
			break; 
		case SDLK_SPACE: newInstruction = ROTATION; 
			break; 
		case SDLK_DOWN: newInstruction = MOVE_DOWN; 
			break; 
		default: newInstruction = NO_INSTRUCTION; 
	}
	return newInstruction; 
}

Piece instruction_loop(Piece piece, Piece nextPiece){
	
	for (int i = 0; i < 20; i++) {
		
		if (falling_piece_animation_delay == 0) {
			return piece;  
		}
		
		enum instruction newInstruction = get_instruction(); 
		piece = apply_instruction(piece, newInstruction); 	
		
		print_piece(piece); 
		update_screen(nextPiece);
		change_type_piece(piece, EMPTY);
		
	}
	return piece; 
}

Piece apply_instruction(Piece piece, enum instruction newInstruction) {
	Piece potentialPiece = piece;

	switch (newInstruction) {
		
		case MOVE_RIGHT:			
			potentialPiece.center.x = potentialPiece.center.x + 1;
			if (!check_exceed_game_field_and_overlapping(potentialPiece)) {
				piece = potentialPiece; 
			}
			break; 
		case MOVE_LEFT:
			potentialPiece.center.x = potentialPiece.center.x - 1;
			if (!check_exceed_game_field_and_overlapping(potentialPiece)) {
				piece = potentialPiece; 
			}
			break; 
		case ROTATION: 
			potentialPiece.rotation = (potentialPiece.rotation + 1) % 4;
			if (!check_exceed_game_field_and_overlapping(potentialPiece)) {
				piece = potentialPiece; 			
			}
			break; 
		case MOVE_DOWN: falling_piece_animation_delay = 0; 
			break; 
		case NO_INSTRUCTION:
			break; 
	}
	
	return piece; 
}

void clean_memory_command() {
	for (int i = 0; i<20; i++) {
		gfx_pollkey(); 
	}
}


/**************************ACTION ON PIECES****************************/

Point find_center_piece(int pieceNumber, int rotation) {
	
	int i = 0, j = 0; 
	
	while (pieceDefinition[pieceNumber][rotation][i][j] != 2) {
		i++; 
		if (i >= 4) {
			i = 0; 
			j++; 
		}
	}
	Point centerPiece; 
	centerPiece.x = i; 
	centerPiece.y = j;
	return centerPiece; 

}

void change_type_piece(Piece piece, enum squareFieldType type) {

	Point centerPiece = find_center_piece(piece.kind, piece.rotation); 
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieceDefinition[piece.kind][piece.rotation][i][j] != 0) {
				gameField[i + piece.center.x - centerPiece.x][j + piece.center.y - centerPiece.y] = type; 
			}
		}
	}	
}

Piece pull_next_piece() {
	
	Piece newPiece; 
	
	newPiece.kind = rand()%7; 
	newPiece.rotation = 0; 
		
	Point centerPiece = find_center_piece(newPiece.kind, newPiece.rotation); 

	newPiece.center.x = (WIDTH_OF_GAME_FIELD / 2) - centerPiece.x;
	newPiece.center.y =  centerPiece.y;  
	 
	return newPiece; 
} 


/**************************ACTION ON LINES*****************************/

void check_all_line() {
	for (int i = 0; i < HEIGHT_OF_GAME_FIELD; i++) {
		if (check_complete_line(i)) {
			deplace_lines(i); 
			score = score + 1; 
			if (delayOfFall > LAST_DELAY_OF_FALL) {
				delayOfFall = delayOfFall - INTERVAL_DELAY_OF_FALL;
			}
		}
	}
}

void deplace_lines(int startingLine) {
	
	for (int j = startingLine; j > 0; j--) {
		for (int i = 0; i < WIDTH_OF_GAME_FIELD; i++) {
				gameField[i][j] = gameField[i][j-1]; 
		}
	}
	for (int i = 0; i < WIDTH_OF_GAME_FIELD; i++) {
				gameField[i][0] = EMPTY; 
		}
}


/****************************BOOL CHECK********************************/

bool is_piece_down(Piece piece) {
	
	Point centerPiece = find_center_piece(piece.kind, piece.rotation); 
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieceDefinition[piece.kind][piece.rotation][i][j] != 0 && j + piece.center.y - centerPiece.y + 1 > HEIGHT_OF_GAME_FIELD - 1) {
				return true; 
			}
			if (pieceDefinition[piece.kind][piece.rotation][i][j] != 0 
					&& gameField[i + piece.center.x - centerPiece.x][j + piece.center.y - centerPiece.y + 1] != EMPTY) {
				return true;  
			}
		}
	}
	
	return false;
	
}

bool check_exceed_game_field_and_overlapping(Piece potentialPiece) {
	
	Point centerPiece = find_center_piece(potentialPiece.kind, potentialPiece.rotation); 
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieceDefinition[potentialPiece.kind][potentialPiece.rotation][i][j] != 0) {
				if ((i + potentialPiece.center.x - centerPiece.x) < 0 || (i + potentialPiece.center.x - centerPiece.x) > WIDTH_OF_GAME_FIELD - 1 
					|| (j + potentialPiece.center.y - centerPiece.y) < 0 || (j + potentialPiece.center.y - centerPiece.y) > HEIGHT_OF_GAME_FIELD - 1) {
					return true; 
				}
				if (gameField[i + potentialPiece.center.x - centerPiece.x][j + potentialPiece.center.y - centerPiece.y] != EMPTY) {
					return true; 
				}
			}
		}
	}	
	
	return false; 
} 

bool check_complete_line(int numberLine) {
	
	for (int i = 0; i < WIDTH_OF_GAME_FIELD; i++) {
		if (gameField[i][numberLine] != GROUND){
			return false; 
		}
	}
	return true; 	
}

bool check_lose(Piece piece) {
	
	if(check_exceed_game_field_and_overlapping(piece)) {
		return true; 
	} 
	return false; 	
}




