
#include <iostream>

#include "board.hpp"

bool unitTest()
{
    std::cout << "Test 1" << std::endl;

    grid_t grid1[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    Board test1(grid1);
    std::cout << test1 << std::endl;
    
    std::cout << "Red moves" << std::endl;
    test1.calculateMoves(IS_RED);
    for(auto move : test1.getMoves())
    {
        std::cout << move << std::endl;
    }

    std::cout << "Black moves" << std::endl;
    test1.calculateMoves(IS_BLACK);
    for(auto move : test1.getMoves())
    {
        std::cout << move << std::endl;
    }
    return true;
}