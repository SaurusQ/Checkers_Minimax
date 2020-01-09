
#ifndef SOLVER_HPP
#define SOVER_HPP

#include <thread>
#include <vector>
#include <future>

#include "move.hpp"
#include "board.hpp"

class Solver
{
    public:
        Solver();
        void setNumCores(unsigned int cores) { cores_ = cores; }
        unsigned int getNumCores() const { return cores_; }
        virtual Move evaluateBestMove(Board& board, int side);
    protected:
        unsigned int cores_;
};

class MiniMax : public Solver
{
    public:
        MiniMax() : Solver() {};
        virtual Move evaluateBestMove(Board& board, int side);
};

#endif
