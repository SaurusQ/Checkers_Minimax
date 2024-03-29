
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
    } while(idx < 0 || idx >= moves.size());
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

MoveLegality Game::tryMove(int x1, int y1, int x2, int y2, std::vector<int> eats)
{
    int idx1 = board_.locationToIndex(x1, y1);
    int idx2 = board_.locationToIndex(x2, y2);
    if(idx1 < 0 || idx2 < 0) return MoveLegality::ILLEGAL;
    if(idx1 == idx2) return MoveLegality::NOTHING;
    if(!board_.isCalculated()) board_.calculateMoves(nextSide_);
    auto& moves = board_.getMoves();

    // check is we need to eat this time
    if((moves[0].getEats().size() == 0) 
        != (eats.size() == 0))
    {
        return MoveLegality::ILLEGAL;
    }

    for(auto& m : moves)
    {
        bool fail = false;
        if(m.getStart() != idx1) continue;              // must start at the same place
        if(m.getEats().size() < eats.size()) continue;  // must have less eats than the move
        for(int i = 0; i < eats.size(); i++)            // if has eats the beginning must be equal
        {
            if(m.getEats()[i] != eats[i])
            {
                fail = true;
                break;
            }
        }
        if(!fail)
        {
            if(m.getEats().size() != eats.size()) return MoveLegality::PARTIAL; // this is partial because the eats are not complete
            if(m.getEnd() == idx2)                      // must have the same end
            {
                board_.executeMove(m);
                nextSide_ = swapSide(nextSide_);
                return MoveLegality::LEGAL;
            }
        }
    }
    return MoveLegality::ILLEGAL;
}
