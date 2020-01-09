
#include <thread>

#include "simulation.hpp"

Simulation::Simulation()
    : board_()
{
    unsigned int cores = std::thread::hardware_concurrency();
    if(cores == 0) cores_ = 8;
    else cores_ = cores;
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

SimBrute::SimBrute()
    : Simulation()
{

}
