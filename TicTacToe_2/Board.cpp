#include "Board.h"

/*
NOTE:
	state values: 0 = empty; 1 = X; 2 = O
*/

Board::Board() {  // creates a new board with no plays on it. 
	for (int i = 0; i < 9; i++) {   // makes all board.state values = 0 (empty)
		state[i] = 0;
	}
	freeSpaces = 9;
	bestMove = -1; // TESTING defaults bestMove to -1 to avoid errors and spot errors.
	score = 0;
}

bool Board::isOver() {
	for (int i = 0; i < 7; i += 3) {
		if (state[i] == state[i + 1] && state[i] == state[i + 2] && state[i] != 0) {  // horizontal checks.
			if (state[i] == 1) score = 10;  // comp wins
			else score = -10;  // human wins
			return true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (state[i] == state[i + 3] && state[i] == state[i + 6] && state[i] != 0) {  // vertical checks.
			if (state[i] == 1) score = 10;  // comp wins
			else score = -10;  // human wins
			return true;
		}
	}
	if (state[0] == state[4] && state[0] == state[8] && state[0] != 0) {  // diagonal check.
		if (state[0] == 1) score = 10;  // comp wins
		else score = -10;  // human wins
		return true;
	}
	if (state[2] == state[4] && state[2] == state[6] && state[2] != 0) {  // other diagonal check.
		if (state[2] == 1) score = 10;  // comp wins
		else score = -10;  // human wins
		return true;
	}
	if (freeSpaces == 0) { // draw check.
		score = 0;
		return true;
	}
	return false;
}

Board::~Board()
{
}
