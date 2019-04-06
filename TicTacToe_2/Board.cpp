#include "Board.h"

/*
NOTE:
	state values: 0 = empty; 1 = X; 2 = O
*/

Board::Board() {
	for (int i = 0; i < 9; i++) {   // makes all board.state values = 0 (empty)
		state[i] = 0;
	}
	freeSpaces = 9;
}

bool Board::isOver() {
	for (int i = 0; i < 7; i += 3) {
		if (state[i] == state[i + 1] && state[i] == state[i + 2] && state[i] != 0) {  // horizontal check.
			return true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (state[i] == state[i + 3] && state[i] == state[i + 6] && state[i] != 0) {  // vertical check.
			return true;
		}
	}
	if (state[0] == state[4] && state[0] == state[8] && state[0] != 0) {  // diagonal check.
		return true;
	}
	if (state[2] == state[4] && state[2] == state[6] && state[2] != 0) {  // other diagonal check.
		return true;
	}
	return false;
}

string Board::toString() {  // returns the board state as a string. 
	string str = "Board State:\n ";
	
	for (int i = 0; i < 9; i++) {
		str += to_string(state[i]);
		if ((i == 2) || (i == 5)) str += "\n";
		str += " ";
	}
	str += "\n";
	return str;
}

Board::~Board()
{
}
