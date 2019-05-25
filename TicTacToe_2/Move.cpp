#include "Move.h"


Move::Move() {
	score = 0;
	moveNum = 0;
}

Move::Move(int state[]) {
	// caluculates score of current move
	score = 0;
	bool isOver = false;
	for (int i = 0; i < 7; i += 3) {
		if (state[i] == state[i + 1] && state[i] == state[i + 2] && state[i] != 0) {  // horizontal check.
			if (state[i] == 1) score++;
			else score--;
			isOver = true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (state[i] == state[i + 3] && state[i] == state[i + 6] && state[i] != 0) {  // vertical check.
			if (state[i] == 1) score++;
			else score--;
			isOver = true;
		}
	}
	if (state[0] == state[4] && state[0] == state[8] && state[0] != 0) {  // diagonal check.
		if (state[0] == 1) score++;
		else score--;
		isOver = true;
	}
	if (state[2] == state[4] && state[2] == state[6] && state[2] != 0) {  // other diagonal check.
		if (state[0] == 1) score++;
		else score--;
		isOver = true;
	}
}

Move::~Move() {
}
