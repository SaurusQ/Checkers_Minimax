
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
        //Create new board and execute move
        pBoards.emplace_back(Board(&board, *it));
        //Start new async operation
        asyncThreads.emplace_back(std::async(std::launch::async, Simulation::minMax, pBranchedSimulation, player, SIMULATION_DEPTH, true, 0x80000000, 0x7FFFFFFF));
    }
    
    //Collect minMax info here
    std::vector<int> movesValue;

    for (auto& element : asyncThreads) 
    {
        movesValue.push_back(element.get());
    }
    
    //All threads have been ended -> free memory
    for(auto pBoard : pBoards)
    {
        delete pBoard;
    }

    //Multimap to store key(int) and result(Move)
    std::multimap<int, Move> mappedMoves;
    if(movesValue.size() != playerMoves.size())
    {
        throw std::length_error("wrong sized vectors when evaluating best move");
    }
    for (size_t i = 0; i < movesValue.size(); i++)
    {
        mappedMoves.insert(std::pair<int, Move>(movesValue[i], playerMoves[i]));
    }
    
    std::vector<Move> equallyBestMoves;
    int bestVal = 0x80000000;//Biggest neg val

    for(std::multimap<int, Move>::reverse_iterator it = mappedMoves.rbegin(); it != mappedMoves.rend(); it++)
    {

        if(bestVal > (*it).first)
            break;
        equallyBestMoves.push_back((*it).second);
        bestVal = std::max(bestVal, (*it).first);
    }

    //Shuffle for randomness in games
    std::random_shuffle(equallyBestMoves.begin(), equallyBestMoves.end());

    //debug print
    for(std::multimap<int, Move>::reverse_iterator it = mappedMoves.rbegin(); it != mappedMoves.rend(); it++)
    {
        std::cout << "key: " << (*it).first << " move: ";
        (*it).second.printMove();
    }
    std::cout << "found: " << equallyBestMoves.size() << " equally good moves\n"; 
    //debug print

    return equallyBestMoves[0];//This is the best move!

}