#pragma once

typedef unsigned long long  U64; // supported by MSC 13.00+ and C99 
#define C64(constantU64) constantU64##ULL

class Move
{
public:
	Move(U64*, U64*, char, char);
	
	// fields 
	bool castle;
	bool promotion;
	bool enPassant;

	U64 positionBefore;
	U64 positionAfter;

	char piece;
	
	// functions 
	char getPeice();
	U64* getPositionBefore();
	U64* getPositionAfter();
		
	bool isSpecialCase();

private:
	

	
};

