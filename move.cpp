
#include "move.hpp"

Move::Move(uint8_t start, uint8_t end)
    : start_(start)
    , end_(end)
{

}

Move::Move(uint8_t start, uint8_t end, uint8_t eatIdx)
    : start_(start)
    , end_(end)
{
    eatIdxs_.push_back(eatIdx);
}

Move::Move(Move move, uint8_t end, uint8_t eatIdx)
    : start_(move.start_)
    , end_(end)
    , eatIdxs_(move.eatIdxs_)
{
    eatIdxs_.push_back(eatIdx);
}

void Move::continueMove(uint8_t end, uint8_t eatIdx)
{
    end_ = end;
    eatIdxs_.push_back(eatIdx);
}

void Move::execute(uint8_t* grid)
{
    grid[end_] = grid[start_];
    grid[start_] = EMPTY;
    //TODO Recursive
}
void Move::undo(uint8_t* grid)
{
    //TODO recursive

    grid[start_] = grid[end_];
    grid[end_] = EMPTY;
}