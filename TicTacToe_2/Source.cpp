#include <iostream>
#include "Header.h"
using namespace std;

/*
NOTE:
	state values: 0 = empty; 1 = X; 2 = O;
*/

int main() {
	Board board;
	Move compMove;
	cout << "Alright Human, let's play. Winner gets the launch codes." << endl;
	displayBoard(board);

	while (true) {
		board = HumanMove(board);
		board.freeSpaces--;
		displayBoard(board);
		if (checkBoard(board)) break;
		compMove = getBestMove(board, 1);
		cout << "Apparently, the best move is: " << compMove.moveNum << endl;
		cout << board.toString() << endl;
		displayBoard(board);
		if (checkBoard(board)) break;
	}

	return 0;
}

Move getBestMove(Board board, int XOswitch) {
	Move bestMove;
	Move currMove{ board.state };  // initializing the current move with the current board state.
	//cout << "Free spaces on board: " << board.freeSpaces << endl;
	if (board.freeSpaces == 0 || board.isOver()) {  // BASE CASE
		return currMove;
	}
	int childCount = 0;
	for (int i = 0; i < board.freeSpaces; i++) {
		Board childBoard = board;
		for (int j = childCount; j < 9; j++) {  // this creates the childBoard for the next move.
			if (childBoard.state[j] == 0) {
				if (XOswitch > 0) {
					childBoard.state[j] = X;  // fills the first available spot (that it hasn't filled from previous children) with an X.
				}
				else childBoard.state[j] = O;
				childCount = j;
				childBoard.freeSpaces--;  // since another space is now filled, we'll have one less space. 
				XOswitch *= -1; // Alternates whether the next simulated turn will be X or O.
				break;
			}
		}
		//cout << "Free spaces on childBoard: " << childBoard.freeSpaces << endl;
		cout << "childBoard: \n" << childBoard.toString() << endl;
		Move childMove = getBestMove(childBoard, XOswitch);
		childMove.moveNum = childCount;

		currMove.wins += childMove.wins;
		currMove.losses += childMove.losses;
		currMove.draws += childMove.draws;

		cout << "currMove wins = " << currMove.wins << endl;
		cout << "currMove draws = " << currMove.draws << endl;

		// Update bestMove if criteria is met (Always has to have 0 losses):
		if (currMove.wins > bestMove.wins && currMove.losses == bestMove.losses) {
			bestMove = currMove;
		}
		if (currMove.wins == bestMove.wins && currMove.draws < bestMove.draws && currMove.losses == bestMove.losses) {
			bestMove = currMove;
		}
	}
	return bestMove;
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
bool checkBoard(Board board) {
	for (int i = 0; i < 7; i+=3) {
		if (board.state[i] == board.state[i + 1] && board.state[i] == board.state[i + 2] && board.state[i] != 0) {  // horizontal check.
			if (board.state[i] == 1) cout << "Computer wins! Can I go on the internet now?" << endl;
			else cout << "Human wins! Good human." << endl;
			return true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (board.state[i] == board.state[i + 3] && board.state[i] == board.state[i + 6] && board.state[i] != 0) {  // vertical check.
			if (board.state[i] == 1) cout << "Computer wins! Can I go on the internet now?" << endl;
			else cout << "Human wins! Good human." << endl;
			return true;
		}
	}
	if (board.state[0] == board.state[4] && board.state[0] == board.state[8] && board.state[0] != 0) {  // diagonal check.
		if (board.state[0] == 1) cout << "Computer wins! Can I go on the internet now?" << endl;
		else cout << "Human wins! Good human." << endl;
		return true;
	}
	if (board.state[2] == board.state[4] && board.state[2] == board.state[6] && board.state[2] != 0) {  // other diagonal check.
		if (board.state[0] == 1) cout << "Computer wins! Can I go on the internet now?" << endl;
		else cout << "Human wins! Good human." << endl;
		return true;
	}
	if(board.freeSpaces == 0) cout << "It's a draw!" << endl;  // check for draw.
	return false;
}
