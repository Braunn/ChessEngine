#include "Position.h"
#include <map>
#include <set>

void Position::initPosition() {
	this->allPieces = Bitboards();
	cout << "Setting up starting position... \n";
	this->allPieces.setUpGame();
	cout << "Done! \n";

	this->ply = 1;
}

// GET MOVE SETS
tuple<Move**, int> Position::getLegalMoves() {
	// check for check/checkmate/stalemate
	U64 allOpponentPseudoAttacks;
	map<char, set<U64>> opponentBBs;
	map<char, set<U64>> friendlyBBs;

	// check for the color of who is moving
	// SPEED?
	if ((this->ply % 2) == 1) {
		opponentBBs = this->allPieces.blackBBs;
		friendlyBBs = this->allPieces.whiteBBs;
	}
	else {
		opponentBBs = this->allPieces.whiteBBs;
		friendlyBBs = this->allPieces.blackBBs;
	}

	U64 kingPos = *friendlyBBs['K'].begin(); // ASSUMES only one bb in king

	// check for horse threats
	U64 areHorsesHere = allPieces.getHorseMoves(&kingPos);


	// get legal moves for each piece that can move
}

// GET LEGAL MOVES HELPERS
/*
struct::move Position::getLegalKingMoves(bool color) {
	return 0;
}

struct::move Position::getLegalQueenMoves(bool color) {
	return 0;
}

struct::move Position::getLegalRookMoves(bool color) {
	return 0;
}

struct::move Position::getLegalBishopMoves(bool color) {
	return 0;
}

struct::move Position::getLegalPawnMoves(bool color) {
	return 0;
}

struct::move Position::getLegalHorseMoves(bool color) {
	this->currentGame->getColorPos(color);
	
	return {0,0};
}
*/