#pragma once
class Move
{
public:
	int wins;
	int losses;
	int draws;
	int moveNum;
	Move();
	Move(int[]);
	~Move();
};

