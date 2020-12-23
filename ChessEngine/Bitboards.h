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
private:
	// ***init with setupgame for bitboards for the start of the game***
	// should include promotions (not yet implemented),\
	// might need to change type to array container
	map<char, set<U64>> blackBBs, whiteBBs;
	U64 getRookMoves(U64*);
};

