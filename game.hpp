
#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

#include "board.hpp"
#include "move.hpp"
#include "solver.hpp"

enum GameType
{
    CPU_VS_CPU,
    PLAYER_VS_CPU,
    CPU_VS_PLAYER,
    PLAYER_VS_PLAYER
};

class Game
{
    public:
        Game(Solver* pSolver, GameType type);
        void nextTurn();
        void printBoard() {std::cout << board_; };
        bool over();
    private:
        void playerTurn(int side);
        void cpuTurn(int side);

        Board board_;
        Solver* pSolver_;
        GameType type_;
        int nextSide_ = IS_BLACK;       //Black side allways starts first
};


#endif
