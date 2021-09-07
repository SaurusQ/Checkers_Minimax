
#ifndef BENCHMARK_DEPTH
#define BENCHMARK_DEPTH 10
#endif

#include <iostream>
#include <memory>

#include "timer.hpp"

int main()
{
    Board testBoard = Board();
    TimeSolver timeSolver = TimeSolver(testBoard);

    std::cout << "----- MiniMax single core (8) -----" << std::endl;
    auto miniMaxSingle = std::make_unique<MiniMax>(8);
    timeSolver.time(miniMaxSingle.get(), false);
    timeSolver.getTime().print(Res::MS);

    std::cout << "----- MiniMaxAB single core (12) -----" << std::endl;
    auto miniMaxABSingle = std::make_unique<MiniMaxAB>(12);
    timeSolver.time(miniMaxABSingle.get(), false);
    timeSolver.getTime().print(Res::MS);

    std::cout << "----- MiniMax multi core (8) -----" << std::endl;
    auto miniMaxMulti = std::make_unique<MiniMax>(8);
    timeSolver.time(miniMaxMulti.get(), true);
    timeSolver.getTime().print(Res::MS);

    std::cout << "----- MiniMaxAB multi core (12) -----" << std::endl;
    auto miniMaxAbMulti = std::make_unique<MiniMaxAB>(12);
    timeSolver.time(miniMaxAbMulti.get(), true);
    timeSolver.getTime().print(Res::MS);
    
    return 0;
}
