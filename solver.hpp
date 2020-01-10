
#ifndef SOLVER_HPP
#define SOVER_HPP

#include <thread>
#include <vector>
#include <future>
#include <map>
#include <limits>
#include <algorithm>

#include "move.hpp"
#include "board.hpp"

class Solver
{
    public:
        Solver(unsigned int depth = SOLVER_DEPTH);
        void setNumCores(unsigned int cores) { cores_ = cores; }
        unsigned int getNumCores() const { return cores_; }
        virtual Move evaluateBestMove(Board& board, int side);
    protected:
        unsigned int cores_;
        unsigned int depth_;
};

class MiniMax : public Solver
{
    public:
        MiniMax() : Solver() {};
        virtual Move evaluateBestMove(Board& board, int side);
        int algorithm(Board board, unsigned int depth, int side, bool maximizingPlayer);
};

#endif
