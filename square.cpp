
#include "square.hpp"

void Square::setSquare(SquareType type, bool king)
{
    type_ = type;
    king_ = king;
}

char Square::getSymbol()
{
    switch (type_)
    {
        case SquareType::EMPTY:
            return S_EMPTY;        
        case SquareType::FRIENDLY:
            if(king_) return S_FRIENDLY_K;
            else return S_FRIENDLY;
        case SquareType::ENEMY:
            if(king_) return S_FRIENDLY_K;
            else return S_FRIENDLY;
    }
}
