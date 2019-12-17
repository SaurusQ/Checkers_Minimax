
#ifndef MOVE_HPP
#define MOVE_HPP

#include "board.hpp"

class Move
{
    public:
        Move(uint8_t start, uint8_t end);
        void execute(Board *board);
        void undo(Board *board);
    private:
        friend class Board;

        uint8_t start_;
        uint8_t end_;
};

#endif
