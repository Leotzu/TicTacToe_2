#pragma once
#include <string>
#include <iostream>
using namespace std;

class Board
{
public:
	int score;
	int bestMove;
	int freeSpaces;
	int state[9];
	bool isOver();
	Board();
	~Board();
};

