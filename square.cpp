
#include "square.hpp"

Square& Square::operator=(const Square &another)
{
    this->pos_ = another.pos_;
    this->king_ = another.king_;
    return *this;
}

std::vector<Move> Square::getPossibleMoves(Board *board, Pos relChainLoc)
{
    Pos curLoc = {pos_.x + relChainLoc.x, pos_.y + relChainLoc.y};
    std::vector<Move> foundMoves;
    foundMoves.reserve(4);
    Dir possibleDirs[4] = {Dir::NA};

    //Up moves
    if(type_ == SquareType::FRIENDLY || king_)
    {
        possibleDirs[0] = Dir::UL;
        possibleDirs[1] = Dir::UR;
    }

    //Down moves
    if(type_ == SquareType::ENEMY || king_)
    {
        possibleDirs[2] = Dir::DL;
        possibleDirs[3] = Dir::DR;
    }

    for(Dir dir : possibleDirs)
    {
        if(dir == Dir::NA) continue;
        
        bool hasEaten = false;
        Square *pNextSquare = board->getSquare(curLoc, dir, 1);
        if(pNextSquare = nullptr) continue;
        
        //Check is there is possibility to eat
        if(this->isEnemy(*pNextSquare))
        {
            pNextSquare = board->getSquare(curLoc, dir, 2);
            if(pNextSquare == nullptr) continue;

            if(pNextSquare->type_ == SquareType::EMPTY)
            {
                hasEaten = true;
            }
            else continue;
            
        }
        //Move there is the place is blank
        else if(pNextSquare->type_ == SquareType::EMPTY)
        {
            //What to do to
            //Remembet the eaten piece at this moment
        }
    }
    return foundMoves;
}

bool Square::isEnemy(const Square &another)
{
    if(this->type_ == SquareType::ENEMY &&
        another.type_ == SquareType::FRIENDLY ||
        this->type_ == SquareType::FRIENDLY &&
        another.type_ == SquareType::ENEMY)
    {
        return true;
    }
    return false;
}

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
    return 'X';
}
