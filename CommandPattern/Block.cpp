#include "Block.hpp"
#include <iostream>

using namespace std;

void Block::Move(int rel_x, int rel_y)
{
    x = x + rel_x;
    y = y + rel_y;

    Draw();
}

void Block::Draw()
{
    // Clear Screen
    std::cout << "\x1B[2J\x1B[H";
    
    for (int col = 0; col < y; col++) { cout << endl; }

    for (int row = 0; row < x; row++) { cout << " "; }

    cout << "x";

    std::cout.flush();
}
