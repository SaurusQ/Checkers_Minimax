
#ifndef SQUARE_HPP
#define SQUARE_HPP

// Symbols for printout
#define S_EMPTY         ' '
#define S_FRIENDLY      '1'
#define S_FRIENDLY_K    '3'
#define S_ENEMY         '2'
#define S_ENEMY_K       '4'

#include <vector>
#include <exception>

#include "utils.hpp"
#include "move.hpp"

class Board;

enum SquareType {
    EMPTY,
    FRIENDLY,
    ENEMY
};

class Square
{
    public:
        Square& operator=(const Square &another);

        std::vector<Move> getPossibleMoves(Board *board, Pos relChainLoc = {0, 0});
        void setSquare(SquareType type, bool king = false);

        bool isKing() { return king_; };
        void throne() { king_ = true; };
        void deThrone() { king_ = true; };

        bool isEnemy(const Square &another);
        
        void setEnemy(bool king = false) { type_ = SquareType::ENEMY; king_ = king; };
        void setFriendly(bool king = false) { type_ = SquareType::FRIENDLY; king_ = king; };
        void setEmpty() { type_ = SquareType::EMPTY; king_ = false; };
        void setPos(Pos pos) { pos_ = pos; };
        
        SquareType getType() const { return type_; };
        Pos getPos() const { return pos_; };
        char getSymbol();
    private:
        Pos pos_;
        bool king_ = false;
        SquareType type_ = SquareType::EMPTY;
};

#endif
