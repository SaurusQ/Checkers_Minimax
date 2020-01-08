
#include "board.hpp"

Board::Board()
    : reds_(SEGMENT * 3)
    , blacks_(SEGMENT * 3)
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

Board::Board(grid_t grid[BOARD_SIZE][BOARD_SIZE])
    : reds_(0)
    , blacks_(0)
{
    //Set board completely empty
    std::memset(grid_, 0, sizeof(grid_) * sizeof(grid_[0]));

    //Iterate over the array and copy it to the game arrays
    int idx = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if((j + i) % 2 == 0)
            {
                switch(grid[i][j])
                {
                    case 3:
                        grid_[idx] |= IS_KING;
                    case 1:
                        grid_[idx] |= IS_BLACK;
                        break;
                    case 4:
                        grid_[idx] |= IS_KING;
                    case 2:
                        grid_[idx] |= IS_RED;
                        break;
                }
                idx++;
                //Set blocks
                if((j + i) % SEGMENT == (SEGMENT / 2))
                {
                    grid_[idx] = BLOCKED;
                    idx++;
                }
            }
        }
    }
}

bool Board::gameOver()
{
    return (reds_ == 0 || blacks_ == 0) || (moves_.size() == 0);
}

void Board::calculateMoves(int side)
{
    int enemy = (side == IS_BLACK) ? IS_RED : IS_BLACK;

    //Empty moves for recalculation
    moves_.clear();
    moves_.reserve(DEF_NEW_MOVES_SIZE);

    for(int i = 0; i < GRID_SIZE; i++)
    {
        //Calculate moves only for pieces on one side
        if(grid_[i] & side)
        {
            if(grid_[i] & IS_KING)          //Kings
            {
                if(!this->eat(i, i, BOTH, enemy))
                {
                    this->moveUp(i);
                    this->moveDown(i);
                }
            }
            else if(grid_[i] & IS_BLACK)    //Black pawns
            {
                if(!this->eat(i, i, DOWN, enemy))
                {
                    this->moveDown(i);
                }
            }
            else if(grid_[i] & IS_RED)      //Red pawns
            {
                if(!this->eat(i, i, UP, enemy))
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

bool Board::eat(int startIdx, int gridIdx, EatDir eatDir, int enemy, std::vector<int> vEat)
{
    bool eaten = false;
    int eatIdx;
    int moveIdx;

    auto findMove = [&]()
    {
        if((grid_[eatIdx] & enemy)
            && (grid_[moveIdx] == EMPTY)
            && (eatDir != BOTH || std::find(vEat.begin(), vEat.end(), eatIdx) == vEat.end()))
        {       //We don't need to check old movements if the piece can move on only one direction
            vEat.push_back(eatIdx);
            this->eat(startIdx, moveIdx, eatDir, enemy, vEat);
            eaten = true;
        }
    };

    //Up
    if((eatDir == UP || eatDir == BOTH)
        && (gridIdx < SEGMENT * 2 + 1))
    {
        //Right
        eatIdx = gridIdx - SEGMENT;
        moveIdx = gridIdx - SEGMENT * 2;
        findMove();

        //Left
        eatIdx = gridIdx - (1 + SEGMENT);
        moveIdx = gridIdx - (1 + SEGMENT) * 2;
        findMove();
    }

    //Down
    if((eatDir == DOWN || eatDir == BOTH)
        && (gridIdx > GRID_SIZE - (SEGMENT * 2 + 1)))
    {
        //Right
        eatIdx = gridIdx + SEGMENT;
        moveIdx = gridIdx + SEGMENT * 2;
        findMove();

        //Left
        eatIdx = gridIdx + (1 + SEGMENT);
        moveIdx = gridIdx + (1 + SEGMENT) * 2;
        findMove();
    }

    //This is the end of move if we can't eat anymore
    if(!eaten && vEat.size() > 0)
    {
        moves_.push_back(Move(startIdx, gridIdx, vEat));
    }
    vEat.pop_back();

    return eaten;
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
