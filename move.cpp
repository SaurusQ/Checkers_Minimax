
#include "move.hpp"

Move::Move(uint8_t start, uint8_t end)
    : start_(start)
    , end_(end)
{

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