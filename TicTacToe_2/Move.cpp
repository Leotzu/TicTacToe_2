#include "Move.h"


Move::Move() {
	wins = 0;
	losses = 0;
	draws = 0;
	moveNum = 0;
}

Move::Move(int state[]) {
	// caluculates wins, losses, draws:
	wins = 0;
	losses = 0;
	draws = 0;
	bool isOver = false;
	for (int i = 0; i < 7; i += 3) {
		if (state[i] == state[i + 1] && state[i] == state[i + 2] && state[i] != 0) {  // horizontal check.
			if (state[i] == 1) wins++;
			else losses++;
			isOver = true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (state[i] == state[i + 3] && state[i] == state[i + 6] && state[i] != 0) {  // vertical check.
			if (state[i] == 1) wins++;
			else losses++;
			isOver = true;
		}
	}
	if (state[0] == state[4] && state[0] == state[8] && state[0] != 0) {  // diagonal check.
		if (state[0] == 1) wins++;
		else losses++;
		isOver = true;
	}
	if (state[2] == state[4] && state[2] == state[6] && state[2] != 0) {  // other diagonal check.
		if (state[0] == 1) wins++;
		else losses++;
		isOver = true;
	}
	if (isOver == false) {  // check for draw.
		int zeroCount = 0;
		for (int i = 0; i < 9; i++) {
			if (state[i] == 0) zeroCount++;
		}
		if (zeroCount == 0) draws++;
	}
}


Move::~Move() {
}
