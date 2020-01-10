
#ifndef MOVE_HPP
#define MOVE_HPP

#include <vector>
#include <algorithm>
#include <ostream>

#include "definitions.hpp"

class Move
{
    public:
        Move(int start, int end);                               //Constructors
        Move(int stat, int end, int eatIdx);
        Move(Move move, int end, int eatIdx);
        Move(int start, int end, std::vector<int> vEat);
        int execute(grid_t* grid);                             //Execute this move on grid and return number of eaten enemies
        
        int getStart() const { return start_; }
        int getEnd() const { return end_; }

        friend std::ostream& operator<<(std::ostream& os, const Move& b);

    private:
        int start_;                         //Start position of move
        int end_;                           //End position of move

        std::vector<int> eatIdxs_;          //All indexes in a grid where pieci is removed
};

#endif
