
#ifndef BOARD_HPP
#define BOARD_HPP

#include "square.hpp"
#include "move.hpp"

#include <vector>

#define BOARD_SIZE 8

class Board
{
    public:
        Board();
        ~Board();
        void recalculateMoves();
        void calculateMoves();
    private:
        Square grid_[BOARD_SIZE][BOARD_SIZE];
        std::vector<Move> allPossibleMoves;
};

#endif
