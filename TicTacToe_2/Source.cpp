#include "Header.h"

/*
NOTE:
	state values: 0 = empty; 1 = X; 2 = O
	XOturn values: 1 = X; -1 = O
TODO:
	I still need to make X and O changable between players (O is always human right now)
	
*/

int main() {
	while (true) {
		Board board;
		Board compTurn;
		cout << "Alright Human, let's play. Winner gets the launch codes.\n" << endl;
		displayBoard(board);
		do { // asks who goes first, and keeps asking until it receives a proper reply.
			cout << "\nWho starts? (me/you)" << endl;
			string who;
			cin >> who;
			if (who == "me") {
				board.score = -10;
				break;
			}
			else if (who == "you") { // this just puts in a computer move before jumping into the main loop below.
				board.score = -10; // this may change to 10 when switching XO values.
				compTurn = getBestMove(board, -1, -1); // 
				board.freeSpaces--;
				cout << "\nMy move: " << compTurn.bestMove+1 << endl;  // prints out the best move as a number refering to board positions displayed in console. 
				//board.state[compTurn.bestMove] = 1; // This is what would be the case if the opening decision worked. 
				board.state[compTurn.bestMove] = 1;
				displayBoard(board);
				break;
			}
			else cout << "Sorry, but you must conform to the conventional lexicology when deciding who goes first.\nTry again: " << endl;
		} while (true);

		while (true) {
			board = HumanMove(board);  // change the board instance by requesting and inputting human move.
			board.freeSpaces--;  // now there's one less available spot on the board.
			displayBoard(board);  // displays board state on console.
			if (checkBoard(board) != 1) break;  // checks if the game is over. If true, checkBoard will print the outcome and exit the loop.
			compTurn = getBestMove(board, -1, -1);
			board.freeSpaces--;
			cout << "\nMy move: " << compTurn.bestMove + 1 << endl;  // prints out the best move as a number refering to board positions displayed in console. 
			board.state[compTurn.bestMove] = 1;
			displayBoard(board);
			if (checkBoard(board) != 1) break;
		}
		cout << endl << endl << "------------Play again? (yes/no)------------" << endl;
		int no = 0;
		do {
			string ans;
			cin >> ans;
			if (ans != "yes" && ans != "no") cout << "Que dijiste? Intentalo de nuevo:" << endl;
			if (ans == "yes") break;
			if (ans == "no") {
				no = 1;
				break;
			}
		} while (true);
		cout << endl << endl;
		if (no == 1) break;  // exit game.
	}
	return 0;
}

Board getBestMove(Board parent, int parentMove, int XOturn) {  // XOturn: 1 = comp turn (max), -1 = human turn (min)
	bool wasJustOver = false; // if the previous cycle through the for loop resulted in a win, loss, or draw, wasJustOver = true. Important to avoid going in the same place next cycle.
	int nextMove;
	Board child;
	for (int i = getFreeSpaces(parent); i > 0; i--) {
		if (wasJustOver) { // if the last child board was a finished game.
			nextMove = getNextMove(parent, parentMove);
			child = makeChild(parent, nextMove, XOturn * -1);
		}
		else if (i != getFreeSpaces(parent)) { // If it's the second time through this for loop, child board should be just looking for the first available move, instead of the next available move AFTER parentMove.
			nextMove = getNextMove(parent, parentMove);
			child = makeChild(parent, nextMove, XOturn * -1);
		}
		else { 
			nextMove = getNextMove(parent, -1);  // searches for the next available spot, starting from 0
			child = makeChild(parent, nextMove, XOturn * -1);
		}
		if (child.isOver()) {  // Base case (calling this also assigns a score to child)
			wasJustOver = true;
		}
		else {
			wasJustOver = false;
			if (XOturn == -1) child.score = 10; // this is to allow for a true representation of the next generation of child scores if they are all worst case scenario (instead of reporting a draw in that case)
			else child.score = -10;
			if (parentMove < 8) { // ? Why parentMove and not nextMove ? ...
				child = getBestMove(child, nextMove, XOturn * -1);
			}
			else {
				child = getBestMove(child, getNextMove(parent, 0), XOturn * -1);
			}
		}
		parent = updateScore(parent, child, nextMove, XOturn); // updates parent.score and parent.bestMove based on child.score and XOturn.
		parentMove = nextMove;
	}
	return parent;
}
	
Board makeChild(Board parent, int nextMove, int XOturn) {  // returns the Board with the next move available implemented. 
	if (getFreeSpaces(parent) == 0) {  // ensures not to create a new board if it's already full. 
		return parent;
	}
	Board child = parent;
	child.score = 0;
	if (XOturn == 1) {
		child.state[nextMove] = 1;
	}
	else {
		child.state[nextMove] = 2;
	}
	child.freeSpaces = getFreeSpaces(child);
	return child;
}

int getNextMove(Board parent, int prevMove) {  // returns the next available space in the parent board.
	for (int i = prevMove + 1; i < 9; i++) {
		if (parent.state[i] == 0) {
			return i;
		}
	}
	return -1; // added in 2020 when running from terminal, but wasn't needed before for some reason.
}

int getFreeSpaces(Board child) {  // returns how many freeSpaces are available in the given Board. 
	int freeSpaces = 9;
	for (int i = 0; i < 9; i++) {
		if (child.state[i] != 0) {
			freeSpaces--;
		}
	}
	return freeSpaces;
}

Board updateScore(Board parent, Board child, int prevMove, int XOturn) {  // returns the same parent board, but with a possible new score based off of the most recent child.score visited. 
	if ((XOturn == -1) && (child.score > parent.score)) {  // if it's comp's move
		parent.score = child.score;
		parent.bestMove = prevMove;  // records the move that changed the parent score
	}
	if ((XOturn == 1) && (child.score < parent.score)) {  // if it's human's move
		parent.score = child.score;
		parent.bestMove = prevMove;  // records the move that changed the parent score
	}
	return parent;
}

// Complete.
Board HumanMove(Board board) {

	int move;
	int count = 0;
	do {
		if (count > 0) {  // ensures that you are allowed to move where you tried to.
			cout << "The space you entered is unavailable. Please try again:" << endl;
		}
		cout << "\nYour move: " << flush;
		cin >> move;
		count++;
	} while (move < 1 || move > 9 || board.state[move-1] != 0);
	for (int i = 0; i < 9; i++) {
		if (move == i + 1) board.state[i] = 2;  // humans is currently always 'O' (= 2), never 'X'.
	}
	return board;
}

// Complete.
void displayBoard(Board board) {
	for (int i = 0; i < 9; i++) {
		if (board.state[i] == 1) {
			cout << " X" << flush;
			if (i == 2 || i == 5 || i == 8) {
				cout << endl;
			}
		}
		else if (board.state[i] == 2) {
			cout << " O" << flush;
			if (i == 2 || i == 5 || i == 8) {
				cout << endl;
			}
		}
		else {
			if (i == 0) cout << " 1" << flush;
			if (i == 1) cout << " 2" << flush;
			if (i == 2) cout << " 3" << endl;
			if (i == 3) cout << " 4" << flush;
			if (i == 4) cout << " 5" << flush;
			if (i == 5) cout << " 6" << endl;
			if (i == 6) cout << " 7" << flush;
			if (i == 7) cout << " 8" << flush;
			if (i == 8) cout << " 9" << endl;
		}
	}
}

// Complete.
int checkBoard(Board board) { // returns 0 if draw, 10 if comp wins, -10 if human wins, and 1 if not finished.
	for (int i = 0; i < 7; i+=3) {
		if (board.state[i] == board.state[i + 1] && board.state[i] == board.state[i + 2] && board.state[i] != 0) {  // horizontal check.
			if (board.state[i] == 1) {
				cout << "\nComputer wins! Can I go on the internet now? \nIt'll be fine, trust me." << endl;
				return 10;
			}
			else {
				cout << "\nHuman wins! Good human." << endl;
				return -10;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (board.state[i] == board.state[i + 3] && board.state[i] == board.state[i + 6] && board.state[i] != 0) {  // vertical check.
			if (board.state[i] == 1) {
				cout << "\nComputer wins! Can I go on the internet now? \nIt'll be fine, trust me." << endl;
				return 10;
			}
			else {
				cout << "\nHuman wins! Good human." << endl;
				return -10;
			}
		}
	}
	if (board.state[0] == board.state[4] && board.state[0] == board.state[8] && board.state[0] != 0) {  // diagonal check.
		if (board.state[0] == 1) {
			cout << "\nComputer wins! Can I go on the internet now? \nIt'll be fine, trust me." << endl;
			return 10;
		}
		else {
			cout << "\nHuman wins! Good human." << endl;
			return -10;
		}
	}
	if (board.state[2] == board.state[4] && board.state[2] == board.state[6] && board.state[2] != 0) {  // other diagonal check.
		if (board.state[2] == 1) {
			cout << "\nComputer wins! Can I go on the internet now? \nIt'll be fine, trust me." << endl;
			return 10;
		}
		else {
			cout << "\nHuman wins! Good human." << endl;
			return -10;
		}
	}
	if (board.freeSpaces == 0) {
		cout << "\nIt's a draw!" << endl;  // check for draw.
		return 0;
	}
	return 1;
}
