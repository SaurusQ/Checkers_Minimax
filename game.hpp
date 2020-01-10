
#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

#include "board.hpp"
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
        Game(Solver solver, GameType type);
        void nextTurn();
    private:
        Board board_;
        Solver solver_;
};


#endif
