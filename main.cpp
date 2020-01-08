
#include <iostream>
#include <thread>

#include "board.hpp"

extern bool unitTest();

int main()
{
    unitTest();

    Board board;
    std::cout << board;
    board.calculateMoves(IS_BLACK);

    for(auto move : board.getMoves())
    {
        std::cout << move;
    }

    for(auto move : board.getMoves())
    {
        std::cout << move;
        move.execute(board.getGrid());
        std::cout << board;
        move.undo(board.getGrid());
        std::cout << board;
    }

    while(1){}
    return 0;
}