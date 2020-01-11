
#include <iostream>
#include <thread>

#include "solver.hpp"
#include "game.hpp"

#include "board.hpp"

extern bool unitTest();

int main()
{
    MiniMax* pMiniMax = new MiniMax(8);
    Game game(pMiniMax, GameType::PLAYER_VS_CPU);
    while(!game.over())
    {   
        game.nextTurn();
        game.printBoard();
    }
    delete pMiniMax;


    //unitTest();

    /*
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
    */
    while(1){}
    return 0;
}