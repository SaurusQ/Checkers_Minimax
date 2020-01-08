#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "board.hpp"
#include "move.hpp"
#include "definitions.hpp"

class Simulation
{
    public:
        Simulation();
        virtual void run(int side);
        virtual void step(int side);

    private:
        Board board_;
};


#endif