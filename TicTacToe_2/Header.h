#pragma once

#include "Board.h"
#include "Move.h"

int X = 1;
int O = 2;

Board HumanMove(Board);
void displayBoard(Board);
Move getBestMove(Board, int);
bool checkBoard(Board);
