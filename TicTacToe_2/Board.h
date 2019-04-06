#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Board
{
public:
	int state[9];
	int freeSpaces;
	string toString();
	bool isOver();
	Board();
	~Board();
};

