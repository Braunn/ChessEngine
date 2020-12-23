#include "Bitboards.h"
#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include <iterator> 
#include <bitset>

using namespace std;

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
	bitString.reserve();
	for (int i = 56; i >= 0; i = i - 7) {
		cout << bitString.substr(i,8) << "\n";
	}
}

U64 Bitboards::getRookMoves(U64* rPos) {
	// might be slow consider creating map for rook moves
	int index = log2(*rPos);

	int up;
	U64 bw = index % 8;
	up = index / 8;

	U64 across = 0;
	U64 vertical = pow(2,up*8);

	for (int i = 0; i < 8; i++) {
		across += (i * 8 + bw);
		if(i != 7){
			vertical = vertical + vertical << 1;
		}
		
	}

	return across & vertical;
}