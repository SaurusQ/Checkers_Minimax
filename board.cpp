
#include "board.hpp"

Board::Board()
    : reds_(0)
    , blacks_(0)
{
    
}

void Board::calculateMoves(bool red)
{
    for(int i = 0; i < GRID_SIZE; i++)
    {
        if(grid_[i] == EMPTY) continue;

        if(red && (grid_[i] & IS_RED))
        {
            this->moveUp(i);
            if(grid_[i] & IS_KING) this->moveDown(i);
        }
        else if(!red && (grid_[i] & IS_BLACK))
        {
            this->moveDown(i);
            if(grid_[i] & IS_KING) this->moveUp(i);
        }
    }
}

void Board::moveUp(int i)
{
    //Can't move any more up
    if(i < SEGMENT) return;

    //Right
    if(grid_[i - SEGMENT] == EMPTY)
        moves_.emplace_back(Move(i, i - SEGMENT));
    //Left
    if(grid_[i - 1 - SEGMENT] == EMPTY)
        moves_.emplace_back(Move(i, i - 1 - SEGMENT));
}

void Board::moveDown(int i)
{
    //Can't move any more down
    if(i > BOARD_SIZE - SEGMENT) return;

    //Left
    if(grid_[i + SEGMENT] == EMPTY)
        moves_.emplace_back(Move(i, i + SEGMENT));
    //Right
    if(grid_[i + 1 + SEGMENT] == EMPTY)
        moves_.emplace_back(Move(i, i + 1 + SEGMENT));
}
