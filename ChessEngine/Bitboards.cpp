#include "Bitboards.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <iterator> 
#include <bitset>
#include <stdint.h>

/*
	for positions of all peices on a board/ in a  game
	methods should handle only locally know information 
	(i.e. not need data of other pieces or outside
	realm of rules and position to perform their task)
*/

using namespace std;

// INIT
Bitboards::Bitboards() {
	
}

void Bitboards::setUpGame() {
	// sets up the intitial posiiton of all pieces before the game is started
	// initial pos already set in 
	
	set<U64> whiteRooks { 0x1, 0x80 };
	set<U64> whiteHorses { 0x02, 0x40 };
	set<U64> whiteBishops { 0x04, 0x20 };
	set<U64> whiteQueens { 0x08 };
	set<U64> whiteKing { 0x10 };
	set<U64> whitePawns {
		0x0100, 0x0200, 0x0400, 0x0800,
		0x1000, 0x2000, 0x4000, 0x8000
	};

	whiteBBs['R'] = whiteRooks;
	whiteBBs['N'] = whiteHorses;
	whiteBBs['B'] = whiteBishops;
	whiteBBs['Q'] = whiteQueens;
	whiteBBs['K'] = whiteKing;
	whiteBBs['P'] = whitePawns;

	set<U64> blackRooks { 0x0100000000000000, 0x8000000000000000 };
	set<U64> blackHorses { 0x0200000000000000 , 0x4000000000000000 };
	set<U64> blackBishops { 0x0400000000000000 , 0x2000000000000000 };
	set<U64> blackQueens { 0x0800000000000000 };
	set<U64> blackKing { 0x1000000000000000 };
	set<U64> blackPawns {
		0x0001000000000000, 0x0002000000000000, 0x0004000000000000, 0x0008000000000000,
		0x0010000000000000, 0x0020000000000000, 0x0040000000000000, 0x0080000000000000
	};

	blackBBs['r'] = blackRooks;
	blackBBs['n'] = blackHorses;
	blackBBs['b'] = blackBishops;
	blackBBs['q'] = blackQueens;
	blackBBs['k'] = blackKing;
	blackBBs['p'] = blackPawns;

}

// DEBUGGING AND DISPLAY
void Bitboards::display() {
	// only works if bitboards are power of 2 
	char bChars[64];
	fill_n(bChars, 64, ' '); 

	// dont copy and paste make nicer!
	map<char, set<U64>> ::iterator itr;
	set<U64> ::iterator bb;
	for (map<char, set<U64>> boards : {whiteBBs, blackBBs}) {
		for (itr = boards.begin(); itr != boards.end(); itr++) {
			for (bb = itr->second.begin(); bb != itr->second.end(); bb++) {
				// doesnt display if zero!
				if (*bb != 0) {
					int index = log2(*bb);
					bChars[index] = itr->first;
				}
			}
		}
	}

	//print populated char array
	for (int r = 56; r >= 0; r = r - 8) {
		cout << "\t|";
		for (int c = 0; c < 8; c++) {
			cout <<bChars[r + c] << '|';
		}
		cout << "\n\t_________________\n";
	}
	
	//cout << "\n" << bChars;
}

void Bitboards::printBB(U64 bb ) {
	// needs to change is board size is changed
	// prints out ones and zeros
	bitset<64> b(bb);

	string bitString = b.to_string();
	for (int i = 0; i < 8; i++) {
		for (int j = 7; j >= 0; j--) {
			cout << bitString[(i*8)+j];
		}
		cout << "\n";
	}

	//cout << "\n\n" << bitString << "\n";
}

// CREATE ATTACKING BITBOARDS

U64 Bitboards::getRookMoves(U64* rPos) {
	// might be slow consider creating map for rook moves
	// can only handle a power of 2 for position

	int index = log2(*rPos);

	int row;
	U64 col = index % 8;
	row = index / 8;

	U64 vertical = (0x0101010101010101) * (int)pow(2, col);
	U64 horizontal = pow(2,8*row)*255; // readble formula: pow(2, (n + 1) * 8) - 1-(pow(2,n*8)-1)

	return horizontal ^ vertical;
	
}

U64 Bitboards::getPawnMoves(U64* pPos, bool color ) {
	// returns all the attacks AND moves a pawn can make
	// might need to be split up due to dealing with a and m differetnly OR
	// handle that elsewhere
	int* rank = new int;
	int* file = new int;
	setRankFileIndex(pPos, rank, file);

	uint8_t bFile = pow(2, *file);
	uint8_t amInFront = (*file) ? 0b111 << *file-1 : 0b11; // attack move in front, the two diagonals + move fw
	U64 tmp = 0;

	// check for color
	if (color) {
		// white -> mv fwd
		tmp = (U64) amInFront << (*rank + 1) * 8;
		if (*rank == 1) {
			// add double move
			tmp |= *pPos << 16;
		}
	}
	else {
		// black -> mv bwd
		tmp = (U64) amInFront << (*rank - 1) * 8;
		if (*rank == 6) {
			// add double move
			tmp |= *pPos >> 16;
		}
	}

	return tmp;
}

U64 Bitboards::getKingMoves(U64* kPos) {
	uint8_t file = pow(2, (int) log2(*kPos) % 8);
	//cout << "file: " << (int) log2(file)+1 << "\n";
	file = (file >> 1 ) | file;
	file = (file << 1) | file;
	//cout << "files: " << (int) file << "\n";
	
	int rank = log2(*kPos) / 8;

	//U64 tmp = pow(2,rank*8)*file;
	//cout << "kPos: " << *kPos << "\n" << "rank: " << rank << "\n";
	U64 wideFile = file;
	U64 tmp = wideFile << (rank * 8);
	//cout << "tmp: " << file << "\n";
	//printBB(file);
	//cout << "\n";
	tmp = (tmp >> 8) | tmp;
	tmp = (tmp << 8) | tmp;
	
	tmp ^= *kPos;
	
	return tmp;
}

U64 Bitboards::getHorseMoves(U64* hPos) {
	int* rank = new int;
	int* file = new int;
	setRankFileIndex(hPos, rank, file);

	uint8_t bFile = pow(2, *file);
	//cout << "rank,  file: " << *rank << ", " << *file << "\n";
	uint8_t closeRow, fartherRow;
	U64 wideTmp = 0;
	int offset = 0;

	closeRow = (bFile << 2) | ( bFile >> 2);
	fartherRow = (bFile << 1) | (bFile >> 1);

	for (int r = 0; r < 8; r++) {
		offset = abs(r-*rank);

		if (offset == 1) {
			wideTmp = wideTmp | ((U64) closeRow << r * 8);
		}
		else if (offset == 2) {
			wideTmp = wideTmp | ((U64) fartherRow << r * 8);
		}
	}

	return wideTmp;
}

U64 Bitboards::getQueenMoves(U64* qPos) {
	return getBishopMoves(qPos) | getRookMoves(qPos);
}

U64 Bitboards::getBishopMoves(U64* bPos) {
	//returns attack moves for bishop
	
	//init important vars from position board  
	int* rank = new int;
	int* file = new int;
	setRankFileIndex(bPos, rank, file);
	
	// get useful vars for shifting
	uint8_t bFile = pow(2,*file);
	cout << "rank,  file: " << *rank << ", " << *file << "\n";
	uint8_t narrowTmp;
	U64 wideTmp = 0;
	int offset = 0;

	for (int r = 0; r < 8; r++) {
		
		narrowTmp = bFile;
		offset = abs(r - *rank); // gets offset row/rank from where pos board is
		narrowTmp = (narrowTmp << offset) | (narrowTmp >> offset);
		
		/* Debugging 
		cout << "## " << r << " ##" << "\n";
		cout << "num: " << (int) narrowTmp << "\n";
		printBB((U64) narrowTmp);
		cout << "\n";
		*/
		
		wideTmp |= (U64) narrowTmp << (r * 8);
	}
	return wideTmp ^= *bPos;
}

// HELPER
void Bitboards::setRankFileIndex(U64* positionOfPiece, int* rank, int* file) {
	// returns rank and file in range 0-7
	int tmp = (int)log2(*positionOfPiece);
	*rank = tmp / 8;
	*file = tmp % 8;
}

// POSITIONS HELPER ... CONSIDER MOVING THERE?
U64 Bitboards::getColorPositions(bool color) {
	// returns the bitboard that represents the positions of all pieces
	// for one color: true for white and false for black
	map<char, set<U64>>* bitboardSets;
	if (color) {
		bitboardSets = &(this->whiteBBs);
	}
	else {
		bitboardSets = &(this->blackBBs);
	}

	U64 tmp = 0;

	map<char, set<U64>> ::iterator itr;
	set<U64> ::iterator bb;
	for (itr = bitboardSets->begin(); itr != bitboardSets->end(); itr++) {
		for (bb = itr->second.begin(); bb != itr->second.end(); bb++) {
			// doesnt display if zero!
			tmp |= *bb;
		}
	}

	return tmp;
}

// UTILITY
U64 Bitboards::getLSB(U64* bb) {
	//return -(signed long long)*bb;
	return *bb & -(signed long long) * bb;
}

U64 Bitboards::getMSB(U64 bb) {
	bb |= bb >> 1;
	bb |= bb >> 2;
	bb |= bb >> 4;
	bb |= bb >> 8;
	bb |= bb >> 16;
	bb |= bb >> 32;

	return (bb >> 1) + 1;
}