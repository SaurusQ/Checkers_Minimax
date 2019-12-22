
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

void Board::calculateMoves(int side)
{
    int enemy = (side == IS_BLACK) ? IS_RED : IS_BLACK;

    for(int i = 0; i < GRID_SIZE; i++)
    {
        //Calculate moves only for pieces on one side
        if(grid_[i] & side)
        {
            if(grid_[i] & IS_KING)          //Kings
            {
                if(!this->eat(i, enemy))
                {
                    this->moveUp(i);
                    this->moveDown(i);
                }
            }
            else if(grid_[i] & IS_BLACK)    //Black pawns
            {
                if(!this->eatDown(i, enemy))
                {
                    this->moveDown(i);
                }
            }
            else if(grid_[i] & IS_RED)      //Red pawns
            {
                if(!this->eatUp(i, enemy))
                {
                    this->moveUp(i);
                }
            }
        }
    }
}

void Board::moveUp(int idx)
{
    //Can't move any more up
    if(idx < SEGMENT) return;
    
    //Right
    if(grid_[idx - SEGMENT] == EMPTY)
        moves_.emplace_back(Move(idx, idx - SEGMENT));
    //Left
    if(grid_[idx - 1 - SEGMENT] == EMPTY)
        moves_.emplace_back(Move(idx, idx - 1 - SEGMENT));
}

void Board::moveDown(int idx)
{
    //Can't move any more down
    if(idx > GRID_SIZE - SEGMENT) return;

    //Left
    if(grid_[idx + SEGMENT] == EMPTY)
        moves_.emplace_back(Move(idx, idx + SEGMENT));
    //Right
    if(grid_[idx + 1 + SEGMENT] == EMPTY)
        moves_.emplace_back(Move(idx, idx + 1 + SEGMENT));
}

bool Board::eatUp(int gridIdx, int enemy, int moveIdx)
{
    //Can't eat up
    if(gridIdx < SEGMENT * 2 + 1) return false;
    
    bool retVal = false;

    //Right
    if((grid_[gridIdx - SEGMENT] & enemy) && (grid_[gridIdx - SEGMENT * 2]))
    {
        if(moveIdx == -1) moves_.emplace_back(Move(gridIdx, gridIdx - SEGMENT * 2, gridIdx - SEGMENT));
        else moves_[moveIdx].continueMove(gridIdx - SEGMENT * 2, gridIdx - SEGMENT);
        this->eatUp(gridIdx - SEGMENT * 2, enemy, moves_.size - 1);
        retVal = true;
    }

    //Left
    if((grid_[gridIdx - 1 - SEGMENT] & enemy) && (grid_[gridIdx - (1 + SEGMENT) * 2]))
    {
        //TODO indexes
        if(moveIdx == -1 && !retVal) moves_.emplace_back(Move(gridIdx, gridIdx - SEGMENT * 2, gridIdx - SEGMENT));
        else moves_[moveIdx].continueMove(gridIdx - SEGMENT * 2, gridIdx - SEGMENT);
        this->eatUp(gridIdx - SEGMENT * 2, enemy, moves_.size - 1);
        retVal = true;
    }
    return retVal;
}

bool Board::eatDown(int gridIdx, int enemy, int moveIdx)
{
    //Can't eat down
    if(gridIdx > GRID_SIZE - (SEGMENT * 2 + 1)) return false;
 
    //Right
    if((grid_[gridIdx + SEGMENT] & enemy) && (grid_[gridIdx + SEGMENT * 2]))
    {

    }

    //Left
    if((grid_[gridIdx + 1 + SEGMENT] & enemy) && (grid_[gridIdx + (1 + SEGMENT) * 2]))
    {
        
    }
}

bool Board::eat(int gridIdx, int enemy, int moveIdx)
{
    //Up
    if(gridIdx < SEGMENT * 2 + 1)
    {
        //Right
        if((grid_[gridIdx - SEGMENT] & enemy) && (grid_[gridIdx - SEGMENT * 2]))
        {

        }

        //Left
        if((grid_[gridIdx - 1 - SEGMENT] & enemy) && (grid_[gridIdx - (1 + SEGMENT) * 2]))
        {

        }
    }

    //Down
    if(gridIdx > GRID_SIZE - (SEGMENT * 2 + 1))
    {
        //Right
        if((grid_[gridIdx + SEGMENT] & enemy) && (grid_[gridIdx + SEGMENT * 2]))
        {

        }

        //Left
        if((grid_[gridIdx + 1 + SEGMENT] & enemy) && (grid_[gridIdx + (1 + SEGMENT) * 2]))
        {
            
        }
    }
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
