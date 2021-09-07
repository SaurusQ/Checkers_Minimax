
#include <iostream>

#include "board.hpp"

int main()
{
    {
        std::cout << "Test 1" << std::endl;

        grid_t grid[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };

        Board test(grid);
        std::cout << test << std::endl;
        
        std::cout << "Red moves" << std::endl;
        test.calculateMoves(IS_RED);
        for(auto move : test.getMoves())
        {
            std::cout << move << std::endl;
        }
        auto moves = test.getMoves();
        if(moves.size() != 1) return -1;
        if(moves[0].getStart() != 15 || moves[0].getEnd() != 5) return -1;

        std::cout << "Black moves" << std::endl;
        test.calculateMoves(IS_BLACK);
        for(auto move : test.getMoves())
        {
            std::cout << move << std::endl;
        }
        moves = test.getMoves();
        if(moves.size() != 1) return -1;
        if(moves[0].getStart() != 10 || moves[0].getEnd() != 20) return -1;
    }
    
    {
        std::cout << "Test 2" << std::endl;

        grid_t grid[8][8] = {
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };

        Board test(grid);
        std::cout << test << std::endl;
        
        std::cout << "Eats" << std::endl;
        test.calculateMoves(IS_BLACK);
        for(auto move : test.getMoves())
        {
            if(move.getStart() != 1 || move.getEnd() != 29) return -1;
            std::cout << move;
        }
    }

    {
        std::cout << "Test 3" << std::endl;

        grid_t grid[8][8] = {
            {0, 0, 0, 0, 1, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };

        Board test(grid);
        std::cout << test << std::endl;
        
        std::cout << "Eats" << std::endl;
        test.calculateMoves(IS_BLACK);
        for(auto move : test.getMoves())
        {
            if(move.getEnd() != 28 && move.getEnd() != 30) return -1;
            std::cout << move;
        }
    }

    {
        std::cout << "Test 4" << std::endl;

        grid_t grid[8][8] = {
            {1, 0, 2, 0, 2, 0, 2, 0},
            {0, 2, 0, 2, 0, 0, 0, 0},
            {2, 0, 2, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0, 1}
        };

        Board test(grid);
        std::cout << test << std::endl;
        
        test.calculateMoves(IS_BLACK);
        std::cout << "#Moves: " << test.getMoves().size() << std::endl;
        for(auto move : test.getMoves())
        {
            std::cout << move;
        }
        if(test.getMoves().size() != 0) return -1;
    }

    {
        std::cout << "Test 5" << std::endl;

        grid_t grid[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 3, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };

        Board test(grid);
        std::cout << test << std::endl;
        
        std::cout << "Eats" << std::endl;
        test.calculateMoves(IS_BLACK);
        for(auto move : test.getMoves())
        {
            if(move.getEnd() != 0 && move.getEnd() != 30) return -1;
            std::cout << move;
        }
    }

    return 0;
}
