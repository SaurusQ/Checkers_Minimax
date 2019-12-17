
#include "move.hpp"

Move::Move(uint8_t start, uint8_t end)
    : start_(start)
    , end_(end)
{

}

void Move::execute(Board* board)
{
    board->grid_[end_] = board->grid_[start_];
    board->grid_[start_] = EMPTY;
    //TODO Recursive
}
void Move::undo(Board* board)
{
    //TODO recursive

    board->grid_[start_] = board->grid_[end_];
    board->grid_[end_] = EMPTY;
}