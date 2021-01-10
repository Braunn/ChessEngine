#include "Move.h"
#include "Bitboards.h"

Move::Move(U64* posB, U64* posA, char piece, char specialCase = 'n') {
	this->positionAfter = *posA;
	this->positionBefore = *posB;

	this->castle = false;
	this->promotion = false;
	this->enPassant = false;

	this->piece = piece;

	if(specialCase != 'n')
		switch (specialCase) {
			case 'c':
				this->castle = true;
				break;
			case 'p':
				this->promotion = true;
				break;
			case 'e':
				this->enPassant = true;
				break;
		}
}


// GETTERS
U64* Move::getPositionBefore() {
	return &this->positionBefore;
}

U64* Move::getPositionAfter() {
	return &this->positionAfter;
}

bool Move::isSpecialCase() {
	return this->castle || this->promotion || this->enPassant;
}

char Move::getPeice() {
	return this->piece;
}