
#ifndef BOARD_HPP
#define BOARD_HPP

#include <inttypes.h>
#include <vector>
#include <ostream>
#include <cstring>

#include "move.hpp"
#include "definitions.hpp"

class Board
{
    public:
        Board();
        
        void calculateMoves(int side);
        unsigned int redAdvantage() { return reds_ - blacks_; };
        unsigned int blackAdvantage() { return blacks_ - reds_; };

        friend std::ostream& operator<<(std::ostream& os, const Board& b);

    private:
        void moveUp(int idx);
        void moveDown(int idx);
        bool eatUp(int idx, int enemy);
        bool eatDown(int idx, int enemy);
        bool eat(int idx, int eneymy);

        friend class Move;

        unsigned int reds_;
        unsigned int blacks_;
        uint8_t grid_[GRID_SIZE];
        std::vector<Move> moves_;
};

#endif
