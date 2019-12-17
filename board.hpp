
#ifndef BOARD_HPP
#define BOARD_HPP

#include <inttypes.h>
#include <vector>

#include "move.hpp"

#define BOARD_SIZE  8
#define SEGMENT     BOARD_SIZE / 2
#define GRID_SIZE   BOARD_SIZE * BOARD_SIZE / 2

#define IS_RED   0x02
#define IS_BLACK 0x01
#define IS_KING  0x04

enum Piece
{
    EMPTY       = 0, //000
    BLACK_PAWN  = 1, //001
    BLACK_KING  = 5, //101
    RED_PAWN    = 2, //010
    RED_KING    = 6  //110
};

class Move;

class Board
{
    public:
        Board();
        ~Board();
        void calculateMoves(bool red);
        unsigned int redAdvantage() { return reds_ - blacks_; };
        unsigned int blackAdvantage() { return blacks_ - reds_; };
    private:
        void moveUp(int idx);
        void moveDown(int idx);

        friend class Move;

        unsigned int reds_;
        unsigned int blacks_;
        uint8_t grid_[GRID_SIZE + SEGMENT];
        std::vector<Move> moves_;
};

#endif
