
#include "board.hpp"

Board::Board()
{
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        for(int y = 0; y < BOARD_SIZE; y++)
        {
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