
#ifndef BOARD_HPP
#define BOARD_HPP

#include <inttypes.h>
#include <vector>
#include <ostream>
#include <cstring>
#include <iostream>
#include <tuple>

#include "move.hpp"
#include "definitions.hpp"

class Board
{
    public:
        Board();
        Board(grid_t grid[BOARD_SIZE][BOARD_SIZE]);
        Board(Board* pBoard, Move& move);                                        //Create new board from old board and execute move on new board
        
        bool gameOver();                                                        //Return if the game has ended, takes moves into account if calculate moves hasbeen called
        int getHeuristicValue(int side);                                        //Returns the heuristic value of the board based on the side
        void calculateMoves(int side);                                          //Calculates all possible moves for one side
        void executeMove(Move move);                                            //Apply move to the board
        unsigned int redAdvantage() { return reds_ - blacks_; }                 //How much advantage reds have
        unsigned int blackAdvantage() { return blacks_ - reds_; }               //How much advantage black have

        friend std::ostream& operator<<(std::ostream& os, const Board& b);      //Print the board to ostream

        std::vector<Move>& getMoves() { return moves_; }
        grid_t* getGrid() { return grid_; }
        unsigned int aliveBlacks() { return blacks_; }
        unsigned int aliveReds() {return reds_; }
    private:
        void moveUp(int idx);                                                   //Helper function to calculate non-eat moves and add to the moves list
        void moveDown(int idx);                                                 //Helper function to calculate non-eat moves and add to the moves list
        bool eat(int startIdx, int gridIdx, EatDir eatDir,
            int enemy, std::vector<int> eaten = std::vector<int>());            //Calculate all possible chained eats and add to the moves list

        friend class Move;

        bool movesCalculated_ = false;      //Indicates if moves_ is populated with right moves
        unsigned int reds_;                 //Number of red pieces
        unsigned int blacks_;               //Number of black pieces
        grid_t grid_[GRID_SIZE];            //Grid stored in interesting way
        std::vector<Move> moves_;           //All possible moves from calculateMoves
};

#endif
