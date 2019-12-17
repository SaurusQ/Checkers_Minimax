
#include "board.hpp"

Board::Board()
    : reds_(0)
    , blacks_(0)
{
    //Set board completely empty
    std::memset(grid_, 0, sizeof(grid_) * sizeof(grid_[0]));
    //Set blacks up
    for(int i = 0; i < 3 * SEGMENT + 2; i++)
    {
        grid_[i] = BLACK_PAWN;
    }
    //Set reds down
    for(int i = GRID_SIZE - (3 * SEGMENT + 2); i < GRID_SIZE; i++)
    {
        grid_[i] = RED_PAWN;
    }
    //Set blocks
    for(int i = SEGMENT; i < GRID_SIZE; i += 2 * SEGMENT + 1)
    {
        grid_[i] = BLOCKED;
    }
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
    if(i > GRID_SIZE - SEGMENT) return;

    //Left
    if(grid_[i + SEGMENT] == EMPTY)
        moves_.emplace_back(Move(i, i + SEGMENT));
    //Right
    if(grid_[i + 1 + SEGMENT] == EMPTY)
        moves_.emplace_back(Move(i, i + 1 + SEGMENT));
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for(int i = 0; i < GRID_SIZE; i++)
    {
        switch (b.grid_[i])
        {
            case EMPTY:
                os << "  ";
                break;
            case RED_PAWN:
                os << "R ";
                break;
            case RED_KING:
                os << "E ";
                break;
            case BLACK_PAWN:
                os << "B ";
                break;
            case BLACK_KING:
                os << "L ";
                break;
            case BLOCKED:
                os << "\n ";
            default:
                break;
        }
        if((i + 1) % (2 * SEGMENT + 1) == 0) os << "\n";
    }
    os << std::endl;
    return os;
}
