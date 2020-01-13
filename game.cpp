
#include "game.hpp"

Game::Game(Solver* pSolver, GameType type)
    : pSolver_(pSolver)
    , board_()
    , type_(type)
{

}

void Game::nextTurn()
{
    if(type_ == GameType::CPU_VS_CPU || 
        (type_ == GameType::CPU_VS_PLAYER && nextSide_ & IS_BLACK) ||
        (type_ == GameType::PLAYER_VS_CPU && nextSide_ & IS_RED))
    {
        this->cpuTurn(nextSide_);
    }
    else
    {
        this->playerTurn(nextSide_);
    }
    nextSide_ = swapSide(nextSide_);
}

void Game::reset()
{
    nextSide_ = IS_BLACK;
    board_ = Board();
}

void Game::playerTurn(int side)
{
    board_.calculateMoves(side);
    auto moves = board_.getMoves();
    std::cout << "Possible moves: (select index)" << std::endl;
    int i = 0;
    for(auto move : moves)
    {
        std::cout << i << ": " << move << std::endl;
        i++;
    }
    int idx;
    do
    {
        std::cin >> idx;
    } while(idx < 0 && idx >= moves.size());
    std::cout << "Player executing: " << moves[idx] << std::endl;
    board_.executeMove(moves[idx]);
}

void Game::cpuTurn(int side)
{
    Move move = pSolver_->evaluateBestMove(board_, side);
    board_.executeMove(move);
    std::cout << "CPU executing: " << move << std::endl;
}

bool Game::over()
{
    return board_.gameOver();
}