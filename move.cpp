
#include "move.hpp"

void Move::execute(Board &board)
{
    //Move the piece
    Square *pStartS = board.getSquare(start_);
    Square *pEndS = board.getSquare(end_);
    *pEndS = *pStartS;
    pStartS->setEmpty();
    //Capture the eaten squre
    if(hasEaten_)
    {
        board.getSquare(eatenSquare_.getPos())->setEmpty();
    }
    if(nextMove != nullptr)
    {
        nextMove->execute(board);
    }
}
void Move::undo(Board &board)
{
    //Go recursively to the other end of the list and fall bask from there
    if(nextMove != nullptr)
    {
        nextMove->undo(board);
    }

    Square *pStartS = board.getSquare(start_);
    Square *pEndS = board.getSquare(end_);
    *pStartS = *pEndS;
    pEndS->setEmpty();
    //Set the eaten piece back to the board
    if(hasEaten_)
    {
        board.setSquare(eatenSquare_, eatenSquare_.getPos());
    }
}