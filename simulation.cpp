
#include "simulation.hpp"

Simulation::Simulation()
    : board_()
{

}

void Simulation::run(int side)
{
    board_.calculateMoves(side);
    while(!board_.gameOver())
    {
        this->step(side);
        side = swapSide(side);
    }
}

void Simulation::step(int side)
{
    
}