
#include <iostream>
#include <thread>

#include "solver.hpp"
#include "game.hpp"

#include "board.hpp"

extern bool unitTest();

int main()
{
    Solver* pSolver = new MiniMaxAB(10);
    Game game(pSolver, GameType::CPU_VS_CPU);
    while(!game.over())
    {   
        game.nextTurn();
        game.printBoard();
    }
    delete pSolver;


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