
#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

#include "board.hpp"
#include "move.hpp"
#include "solver.hpp"

enum class GameType
{
    CPU_VS_CPU,
    PLAYER_VS_CPU,
    CPU_VS_PLAYER,
    PLAYER_VS_PLAYER
};

enum class MoveLegality
{
    ILLEGAL,
    LEGAL,
    PARTIAL,
    NOTHING
};

class Game
{
    public:
        Game(Solver* pSolver, GameType type);
        void nextTurn();
        void reset();
        bool over();
        MoveLegality tryMove(int x1, int y1, int x2, int y2);
        void setSolver(Solver* pSolver) { pSolver_ = pSolver; }
        void setType(GameType type) { type_ = type; }
        void printBoard() { std::cout << board_; }
        const Board getBoard() { return board_; }
    private:
        void playerTurn(int side);
        void cpuTurn(int side);

        Board board_;
        Solver* pSolver_;
        GameType type_;
        int nextSide_ = IS_BLACK;       //Black side allways starts first
};


#endif
