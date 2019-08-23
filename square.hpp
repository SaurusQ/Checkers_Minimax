
#ifndef SQUARE_HPP
#define SQUARE_HPP

// Symbols for printout
#define S_EMPTY         ' '
#define S_FRIENDLY      '1'
#define S_FRIENDLY_K    '3'
#define S_ENEMY         '2'
#define S_ENEMY_K       '4'

enum SquareType {
    EMPTY,
    FRIENDLY,
    ENEMY
};

class Square
{
    public:
        void setSquare(SquareType type, bool king = false);
        bool isKing() { return king_; };
        void throne() { king_ = true; };
        void deThrone() { king_ = true; };
        
        void setEnemy() { type_ = SquareType::ENEMY; };
        void setFriendly() { type_ = SquareType::ENEMY; };
        
        char getSymbol();
    private:
        bool king_ = false;
        SquareType type_ = EMPTY;

};

#endif
