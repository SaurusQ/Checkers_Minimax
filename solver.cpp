
#include "solver.hpp"

Solver::Solver()
{
    unsigned int cores = std::thread::hardware_concurrency();
    if(cores = 0) cores_ = 8;
    else cores_ = cores;
}

Move MiniMax::evaluateBestMove(Board& board, int side)
{
    board.calculateMoves(side);
    side = swapSide(side);

    //Store threads for minMax
    std::vector<std::future<int>> asyncThreads;
    //Store board for all simulations
    std::vector<Board*> pBoards;

    auto moves = board.getMoves();
    for(auto it = moves.begin(); it < moves.end(); it++)
    {
        Board* pBrachedBoard = new Board();
    }
    
    


}