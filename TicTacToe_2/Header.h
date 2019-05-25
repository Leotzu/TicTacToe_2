#pragma once

#include "Board.h"
#include "Move.h"
#include <iostream>
using namespace std;

int X = 1;
int O = 2;

Board HumanMove(Board);
void displayBoard(Board);
Board getBestMove(Board, int, int);
Board makeChild(Board, int, int);
int getNextMove(Board, int);
int getFreeSpaces(Board);
Board updateScore(Board, Board, int, int);
int checkBoard(Board);
