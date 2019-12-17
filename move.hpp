
#ifndef MOVE_HPP
#define MOVE_HPP

#include <inttypes.h>

#include "definitions.hpp"

class Move
{
    public:
        Move(uint8_t start, uint8_t end);
        void execute(uint8_t* grid);
        void undo(uint8_t* grid);
    private:
        

        uint8_t start_;
        uint8_t end_;
};

#endif
