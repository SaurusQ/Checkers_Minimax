
#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#define DEF_NEW_MOVES_SIZE 10
#define SOLVER_DEPTH 5

#define BOARD_SIZE  8
#define SEGMENT     (BOARD_SIZE / 2)
#define GRID_SIZE   (BOARD_SIZE * BOARD_SIZE / 2 + SEGMENT)

#define IS_RED   0x02
#define IS_BLACK 0x01
#define IS_KING  0x04
#define IS_PIECE (IS_RED | IS_BLACK)

#define swapSide(s) (s == IS_BLACK ? IS_RED : IS_BLACK)

typedef uint8_t grid_t;

enum Piece
{
    EMPTY       = 0, //0000
    BLACK_PAWN  = 1, //0001
    BLACK_KING  = 5, //0101
    RED_PAWN    = 2, //0010
    RED_KING    = 6, //0110
    BLOCKED     = 8  //1000
};

enum EatDir
{
    UP,
    DOWN,
    BOTH
};

#endif
