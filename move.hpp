
#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

#include "utils.hpp"
#include "square.hpp"

class Board;

class Move
{
    public:
        void execute(Board *board);
        void undo(Board *board);

    private:
        Pos start_;
        Pos end_;
        Square eatenSquare_;
        bool hasEaten_ = false;
        Move *nextMove = nullptr;
};

#endif
