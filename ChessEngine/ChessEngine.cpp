// ChessEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Bitboards.h"
#include "SearchNode.h"
#include "Move.h"

// CONVENTIONAL GAME FUNCTIONS
void createGame();
bool getUserColor();

// TEST FUNCTIONS
void testGetMove();
void testSupportBoards();
void testUtility();

using namespace std;

int main()
{
    /*
        NOTES
        MAGIC BBs:
            https://stackoverflow.com/questions/30680559/how-to-find-magic-bitboards
            https://www.chessprogramming.org/Magic_Bitboards

    */
    
    //testSupportBoards();
    //testGetMove();
    //testUtility();
    cout << "COLOR: " << getUserColor();

}

void createGame() {

}

/*
void startNewGame(bool random) {
    this->allPieces = Bitboards();
    this->allPieces.setUpGame();

    this->color = (random) ? rand() % 1 : getUserColor();
}
*/

bool getUserColor() {
    string input;
    cout << "Would you like to play as White or Black?: \n";
    cin >> input;

    while ((input.compare((string) "White") != 0) && (input.compare((string) "Black") != 0)) {
        cout << "Please type either 'Black' or 'White':\n";
        cin >> input;
    }

    return (input == "Black") ? false : true;
}

// ******************
// * TEST FUNCTIONS *
// ******************
void testSupportBoards() {
    Bitboards* b = new Bitboards();
    b->setUpGame();
    b->display();

    cout << "Colored pieces: " << "\n\n";
    b->printBB(b->getColorPositions(false));
}

void testUtility() {
    U64 num = 0x1000000F08006000;
    Bitboards* b = new Bitboards();
    cout << "Number: \n";
    b->printBB(num);
    cout << "LSB: \n";
    b->printBB(b->getLSB(&num));
    cout << "MSB: \n";
    b->printBB(b->getMSB(num));
}

void testGetMove() {
    Bitboards* b = new Bitboards();
    //b->setUpGame();
    //b->display();
    
    U64 testPos = 0x0080000000000000;
    cout << "Test position: \n";
    b->printBB(testPos);
    cout << "Attack Pattern: \n";
    U64 attack = b->getQueenMoves(&testPos);
    //cout << "attack: " << attack << "\n\n";

    b->printBB(attack);
    //cout << "pow: " << log2(0x0000000000000001);
    //cout << "Cast test: " << (int)(uint8_t)0x102;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

void moveObj() {
    Move m = Move();
}