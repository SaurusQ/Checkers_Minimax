
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
    grid[end_] = grid[start_];
    grid[start_] = EMPTY;

    //Eat pices
    eatPieces_.reserve(eatIdxs_.size());
    for(auto i : eatIdxs_)
    {
        eatPieces_.push_back(grid[i]);
        grid[i] = EMPTY;
    }

    return eatIdxs_.size();
}
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

std::ostream& operator<<(std::ostream& os, const Move& b)
{
    os << "Move: s: " << b.start_ << " e: " << b.end_ << std::endl;
    return os;
}
