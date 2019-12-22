
#ifndef MOVE_HPP
#define MOVE_HPP

#include <inttypes.h>
#include <vector>
#include <algorithm>

#include "definitions.hpp"

class Move
{
    public:
        Move(int start, int end);                               //Constructors
        Move(int stat, int end, int eatIdx);
        Move(Move move, int end, int eatIdx);
        Move(int start, int end, std::vector<int> vEat);
        void continueMove(int end, int eatIdx);                 //Add one more move to chained eats
        int execute(int* grid);                                 //Execute this move on grid and return number of eaten enemies
        int undo(int* grid);                                    //Undo this move on grid and return number of returned enemies
    private:
        int start_;                         //Start position of move
        int end_;                           //End position of move

        std::vector<int> eatIdxs_;          //All indexes in a grid where pieci is removed
        std::vector<int> eatPieces_;        //Storage for pieces that were eaten
};

#endif
