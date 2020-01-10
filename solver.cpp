
#include "solver.hpp"

Solver::Solver(unsigned int depth)
    : depth_(depth)
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

    for (auto& thread : asyncThreads) 
    {
        movesValue.push_back(thread.get());
    }
    
    //All threads have been ended -> free memory
    for(auto pBoard : pBoards)
    {
        delete pBoard;
    }

    //Multimap to store key(int) and result(Move)
    std::multimap<int, Move> mappedMoves;
    if(movesValue.size() != moves.size())
    {
        throw std::length_error("wrong sized vectors when evaluating best move");
    }
    for (size_t i = 0; i < movesValue.size(); i++)
    {
        mappedMoves.insert(std::pair<int, Move>(movesValue[i], moves[i]));
    }
    
    std::vector<Move> equallyBestMoves;
    int bestVal = std::numeric_limits<int>::min();

    for(auto it = mappedMoves.rbegin(); it != mappedMoves.rend(); it++)
    {

        if(bestVal > it->first)
            break;
        equallyBestMoves.push_back(it->second);
        bestVal = std::max(bestVal, it->first);
    }

    //Shuffle for randomness in games
    std::random_shuffle(equallyBestMoves.begin(), equallyBestMoves.end());

    //debug print
    for(auto it = mappedMoves.rbegin(); it != mappedMoves.rend(); it++)
    {
        std::cout << "key: " << it->first << " move: ";
        std::cout << it->second;
    }
    std::cout << "found: " << equallyBestMoves.size() << " equally good moves\n"; 
    //debug print

    return equallyBestMoves[0];//This is the best move!
}

int MiniMax::algorithm(Board board, unsigned int depth, int side, bool maximizingPlayer)
{
    int value;
    board.calculateMoves(side);
    if(depth = 0 || board.gameOver())
    {
        if(board.gameOver())
        {
            if(maximizingPlayer) return std::numeric_limits<int>::min();
            else return std::numeric_limits<int>::max();
        }
    }

    if(maximizingPlayer)
    {
        value = std::numeric_limits<int>::min();
        for(auto& move : board.getMoves())
        {

        }

    }
    else
    {
        value = std::numeric_limits<int>::max();
    }
    return value;
}