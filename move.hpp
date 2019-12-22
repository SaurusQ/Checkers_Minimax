
#ifndef MOVE_HPP
#define MOVE_HPP

#include <inttypes.h>
#include <vector>

#include "definitions.hpp"

class Move
{
    public:
        Move(uint8_t start, uint8_t end);
        Move(uint8_t stat, uint8_t end, uint8_t eatIdx);
        Move(Move move, uint8_t end, uint8_t eatIdx);
        void continueMove(uint8_t end, uint8_t eatIdx);
        void execute(uint8_t* grid);
        void undo(uint8_t* grid);
    private:
        uint8_t start_;
        uint8_t end_;

        std::vector<uint8_t> eatIdxs_;
        std::vector<uint8_t> eatPieces_;
};

#endif
