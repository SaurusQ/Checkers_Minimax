
#include "board.hpp"

Board::Board()
{
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        for(int y = 0; y < BOARD_SIZE; y++)
        {
            grid_[x][y].setPos(Pos{x, y});
            if(x + y % 2 && x + y < BOARD_SIZE * 3)
            {
                grid_[x][y].setEnemy();
            }
            else if(x + y % 2 && x + y < BOARD_SIZE * (BOARD_SIZE - 3))
            {
                grid_[x][y].setFriendly();
            }
        }
    }
}

void Board::recalculateMoves()
{
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        for(int y = 0; y < BOARD_SIZE; y++)
        {

        }
    }
}

void Board::calculateMoves()
{

}

void Board::setSquare(const Square &square, Pos pos)
{
    grid_[pos.x][pos.y] = square;
}

Square* Board::getSquare(Pos pos, Dir dir, int length)
{
    Pos relPos;
    switch(dir)
    {
        case Dir::UR:
            relPos = Pos{length, -length};
            break;
        case Dir::UL:
            relPos = Pos{-length, -length};
            break;
        case Dir::DR:
            relPos = Pos{length, length};
            break;
        case Dir::DL:
            relPos = Pos{-length, length};
            break;
        default:
            break;
    }
    pos = Pos{pos.x + relPos.x, pos.y + relPos.y};
    if(pos.x < 0 || pos.y < 0 || pos.x >= BOARD_SIZE || pos.y >= BOARD_SIZE)
    {
        return nullptr;
    }
    else
    {
        return &grid_[pos.x][pos.y];
    }
}