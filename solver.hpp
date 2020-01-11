
#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <thread>
#include <vector>
#include <future>
#include <map>
#include <limits>
#include <algorithm>
#include <random>

#include "move.hpp"
#include "board.hpp"

class Solver
{
    public:
        Solver(unsigned int depth = SOLVER_DEPTH);
        virtual ~Solver() {};

        void setNumCores(unsigned int cores) { cores_ = cores; }
        void setDepth(unsigned int depth) { depth_ = depth; }
        unsigned int getNumCores() const { return cores_; }
        unsigned int getDepth() const { return depth_; }

        virtual Move evaluateBestMove(Board& board, int side) = 0;
    protected:
        unsigned int cores_;
        unsigned int depth_;
        int heuristicMaxSide_;
};

class MiniMax : public Solver
{
    public:
        MiniMax(unsigned int depth = SOLVER_DEPTH) : Solver(depth) {};
        virtual ~MiniMax() {};
        Move evaluateBestMove(Board& board, int side);
        int algorithm(Board board, unsigned int depth, int side, bool maximizingPlayer);
};

#endif
