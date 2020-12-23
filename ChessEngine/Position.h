#pragma once
#include "Bitboards.h"

class Position {

public:
	void startNewGame();
	void startGameFromPosition(Bitboards);
	void makeMove(string);
private:
	Bitboards current;
	int ply;
};

