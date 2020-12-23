// ChessEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Bitboards.h"
#include <iostream>

using namespace std;

int main()
{
    
    Bitboards* b = new Bitboards();
    b->setUpGame();
    b->display();
    
    //b->printBB(0x0000000000000001);
    
  }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

