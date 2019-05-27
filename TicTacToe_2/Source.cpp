#include "Header.h"

/*
NOTE:
	state values: 0 = empty; 1 = X; 2 = O
*/

int main() {
	Board board;
	/*
	// TESTING:
	board.state[0] = 2;
	board.state[2] = 1;
	board.state[3] = 1;
	board.state[5] = 1;
	board.state[7] = 2;
	board.state[8] = 2;
	*/

	Board compMove;  
	cout << "Alright Human, let's play. Winner gets the launch codes." << endl;
	displayBoard(board);
	cout << "Who starts, me or you?" << endl;
	string who;
	cin >> who;
	if (who == "me") {}
	else if (who == "you") {  // I still need to make X and O changable between players (O is always human right now)
		// something needs to go here so that the computer or human goes first (which ever isn't the default 
		// inside the while loop below.
	}

	while (true) {
		board = HumanMove(board);  // change the board instance by requesting and inputting human move.
		board.freeSpaces--;  // now there's one less available spot on the board.
		displayBoard(board);  // displays board state on console.
		if (checkBoard(board) != 1) break;  // checks if the game is over. If true, checkBoard will print the outcome and exit the loop.
		compMove = getBestMove(board, -1, -1);
		cout << "Apparently, the best move is: " << compMove.bestMove << endl;  // prints out the best move as a number refering to board positions displayed in console. 
		break;  // TESTING: this is just here to remove the error everytime compMove.bestMove is not from 1 to 9.

		board.state[compMove.bestMove] = 1;
		displayBoard(board);
		if (checkBoard(board) != 1) break;
	}

	return 0;
}

Board getBestMove(Board parent, int parentMove, int XOswitch) {  // XOswitch: 1 = comp turn (max), -1 = human turn (min)
	// int code = rand();  // TESTNG
	bool wasJustOver = false; // if the previous cycle through the for loop resulted in a win, loss, or draw, wasJustOver = true. Important to avoid going in the same place next cycle.
	for (int i = getFreeSpaces(parent); i > 0; i--) {
		cout << "parentMove: " << parentMove << endl; // TESTING
		cout << "wasJustOver: " << wasJustOver << endl;  // TESTING
		Board child;  // have to initialize it first to avoid errors in my TESTING lines. This could be removed after TESTING is finished. 
		int nextMove;
		if (wasJustOver) {
			nextMove = getNextMove(parent, parentMove);
			cout << "nextMove for makeChild (wasJustOver): " << nextMove << endl;
			child = makeChild(parent, nextMove, XOswitch * -1);
		}
		// If it's the second time through this for loop, child board should be just looking for the first available move, instead 
		// of the next available move AFTER parentMove.
		else { 
			cout << "---NEXTMOVE STARTING FROM 0---" << endl; // TESTING
			nextMove = getNextMove(parent, -1);
			child = makeChild(parent, nextMove, XOswitch * -1);
		}
		{
			cout << "parent board: " << endl; // TESTING
			displayBoard(parent); // TESTING
			cout << "child board: " << endl; // TESTING
			displayBoard(child); // TESTING
			cout << endl; // TESTING
		}
		if (child.isOver()) {  // Base case (calling this also assigns a score to child)
			cout << "child.isOver()" << endl;  // TESTING
			parent = updateScore(parent, child, parentMove, XOswitch); // updates parent score and bestMove based on child.score and XOswitch.
			wasJustOver = true;
			parentMove = nextMove;
		}
		else {
			parentMove = getNextMove(parent, parentMove);  // finds the next available move after the current parentMove.
			wasJustOver = false;
			if (parentMove < 8) {
				child = getBestMove(child, parentMove, XOswitch * -1);
				// parentMove++;
				// XOswitch *= -1;
			}
			else {
				child = getBestMove(child, getNextMove(parent, 0), XOswitch * -1);
			}
		}
	}
	cout << "end of getBestMove cycle." << endl; // TESTING
	cout << "bestMove is: " << parent.bestMove << endl;
	return parent;
}
	
	/* Regarding the above code intention:
	
	I need a parent node on the tree so that when I hit a leaf, I can navigate one backwards to the previous
	board state (moving "childCount" one forward to not go down that same path again). I need to also somehow
	keep track of the various scores at every level I come across (and which XOswitch I'm on at that point) in
	order to decide what score value gets sent back to their common parent (either max score or min score depending 
	on XOswitch). 

	Solution: 

	Every time a parent drops down into a child node where the game is over, the child node will go back up to the
	parent. If the score of the child (+10 if AI wins, or -10 if Human wins) is greater than the current score of 
	parent AND the child's turn was the AI, then the parent stores that as the new best possible score and also
	records the move position of that child. 
	If, instead, the child's turn was the Human AND the score of the child is less than the current parent score,
	then that child's score will be the new parent score, and the parent will record the move position of that
	child. 

	I will still need something like the primary for loop below, but I need to have a way of knowing if I've gone 
	through all the child nodes of the parent node, at which time it'll send back up to that parent node's 
	parent node.
	
	*/

Board makeChild(Board parent, int nextMove, int XOswitch) {  // returns the Board with the next move available implemented. 
	if (getFreeSpaces(parent) == 0) {  // ensures not to create a new board if it's already full. 
		return parent;
	}
	Board child = parent;
	if (XOswitch == 1) {
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

Board updateScore(Board parent, Board child, int prevMove, int XOswitch) {  // returns the same parent board, but with a possible new score based off of the most recent child.score visited. 
	if ((XOswitch == 1) && (child.score > parent.score)) {  // if it's comp's move
		parent.score = child.score;
		parent.bestMove = prevMove;  // records the move that changed the parent score
		cout << "new parent.bestMove: " << parent.bestMove << endl;  // TESTING
	}
	if ((XOswitch == -1) && (child.score < parent.score)) {  // if it's human's move
		parent.score = child.score;
		parent.bestMove = prevMove;  // records the move that changed the parent score
		cout << "new parent.bestMove: " << parent.bestMove << endl;  // TESTING
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
		cout << "Your move: " << flush;
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
				cout << "Computer wins! Can I go on the internet now?" << endl;
				return 10;
			}
			else {
				cout << "Human wins! Good human." << endl;
				return -10;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (board.state[i] == board.state[i + 3] && board.state[i] == board.state[i + 6] && board.state[i] != 0) {  // vertical check.
			if (board.state[i] == 1) {
				cout << "Computer wins! Can I go on the internet now?" << endl;
				return 10;
			}
			else {
				cout << "Human wins! Good human." << endl;
				return -10;
			}
		}
	}
	if (board.state[0] == board.state[4] && board.state[0] == board.state[8] && board.state[0] != 0) {  // diagonal check.
		if (board.state[0] == 1) {
			cout << "Computer wins! Can I go on the internet now?" << endl;
			return 10;
		}
		else {
			cout << "Human wins! Good human." << endl;
			return -10;
		}
	}
	if (board.state[2] == board.state[4] && board.state[2] == board.state[6] && board.state[2] != 0) {  // other diagonal check.
		if (board.state[0] == 1) {
			cout << "Computer wins! Can I go on the internet now?" << endl;
			return 10;
		}
		else {
			cout << "Human wins! Good human." << endl;
			return -10;
		}
	}
	if (board.freeSpaces == 0) {
		cout << "It's a draw!" << endl;  // check for draw.
		return 0;
	}
	return 1;
}
