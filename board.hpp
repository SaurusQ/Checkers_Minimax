
#ifndef BOARD_HPP
#define BOARD_HPP

#define BOARD_SIZE 8

#include "utils.hpp"
#include "square.hpp"

class Board
{
    public:
        Board();
        ~Board();
        void recalculateMoves();
        void calculateMoves();
        void setSquare(const Square &square, Pos pos);

        Square* getSquare(Pos pos, Dir dir = Dir::NA, int length = 0); //Will raise exception if index is out of bounds
    private:
        Square grid_[BOARD_SIZE][BOARD_SIZE];
};

#endif
