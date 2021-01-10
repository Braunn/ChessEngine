#pragma once
#include <iostream>
#include <iterator>
#include <map>
#include <set>

using namespace std;

typedef unsigned long long  U64; // supported by MSC 13.00+ and C99 
#define C64(constantU64) constantU64##ULL

class Bitboards
{
public:
	Bitboards();
	void setUpGame();
	void display();
	void printBB(U64);

	map<char, set<U64>> blackBBs, whiteBBs;
	// change these to return pointers for speed up?
	U64 getRookMoves(U64*); // all good... maybe castling?
	U64 getPawnMoves(U64*, bool); // add en passent? 
	U64 getKingMoves(U64*); // add castling?
	U64 getHorseMoves(U64*);
	U64 getQueenMoves(U64*);
	U64 getBishopMoves(U64*);
	U64 getColorPositions(bool);
	U64 getLSB(U64*);
	U64 getMSB(U64);

private:
	void setRankFileIndex(U64*, int*, int*);
	// ***init with setupgame for bitboards for the start of the game***
	// should include promotions (not yet implemented),\
	// might need to change type to array container
	
};

