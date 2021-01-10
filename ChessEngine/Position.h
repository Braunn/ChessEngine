#pragma once
#include "Bitboards.h"
#include "Move.h"

class Position {

public:
	void initPosition();
	void startAtPosition(Bitboards); // save this feature for later not sure how to implement right now: will all positions have to start at init state? 
	void makeMove();
	void unmakeMove();

	// get legal moves 
	tuple<Move**, int> getLegalMoves();
	/*
	struct::move getLegalKingMoves(bool);
	struct::move getLegalQueenMoves(bool);
	struct::move getLegalRookMoves(bool);
	struct::move getLegalBishopMoves(bool);
	struct::move getLegalPawnMoves(bool);
	struct::move getLegalHorseMoves(bool);
	*/

	Bitboards allPieces;
	int ply;
};

