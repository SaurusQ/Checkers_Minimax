
#include "move.hpp"

Move::Move(int start, int end)
    : start_(start)
    , end_(end)
{

}

Move::Move(int start, int end, int eatIdx)
    : start_(start)
    , end_(end)
{
    eatIdxs_.push_back(eatIdx);
}

Move::Move(Move move, int end, int eatIdx)
    : start_(move.start_)
    , end_(end)
    , eatIdxs_(move.eatIdxs_)
{
    eatIdxs_.push_back(eatIdx);
}

Move::Move(int start, int end, std::vector<int> vEat)
    : start_(start)
    , end_(end)
    , eatIdxs_(vEat)
{

}

int Move::execute(grid_t* grid)
{
    if(end_ < SEGMENT || end_ >= GRID_SIZE - SEGMENT)
        grid[end_] = grid[start_] & IS_KING; //Make king if the piece arrives at the other end
    else
        grid[end_] = grid[start_];
    
    grid[start_] = EMPTY;
    
    //Eat pices
    for(auto i : eatIdxs_)
    {
        grid[i] = EMPTY;
    }
    //Return how many pieces were eaten
    return eatIdxs_.size();
}

/*
int Move::undo(grid_t* grid)
{
    grid[start_] = grid[end_];
    grid[end_] = EMPTY;

    //Put back pieces
    for(int i  = 0; i < eatIdxs_.size(); i++)
    {
        grid[i] == eatPieces_[i];
    }
    eatPieces_.clear();

    return eatIdxs_.size();
}
*/

std::ostream& operator<<(std::ostream& os, const Move& b)
{
    os << "Move: s: " << b.start_ << " e: " << b.end_ << " eat:";
    for(auto idx : b.eatIdxs_)
    {
        os << " " << idx;
    }
    return os;
}
