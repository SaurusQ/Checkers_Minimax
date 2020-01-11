
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

void Game::playerTurn(int side)
{

}

void Game::cpuTurn(int side)
{
    Move move = pSolver_->evaluateBestMove(board_, side);
    board_.executeMove(move);
    std::cout << "CPU executing: " << move << std::endl;
}
