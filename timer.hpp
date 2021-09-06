
#include <chrono>
#include <iostream>
#include <string>

#include "board.hpp"
#include "solver.hpp"

using timePoint = std::chrono::high_resolution_clock::time_point;

enum class Res
{
    S,
    MS,
    US,
    NS
};

class Timer
{
    public:
        Timer() {}
        void start();
        void end();
        void measureFunc(void (*func)());
        void measureFunc(std::function<void()> const& lambda);
        void print(Res resolution = Res::MS) const;
        uint64_t getS() const;
        uint64_t getMs() const;
        uint64_t getUs() const;
        uint64_t getNs() const;

    private:
        bool isValid() const;

        bool valid_ = false;
        bool running_ = false;
        timePoint start_;
        timePoint end_;
};

class TimeSolver
{
    public:
        TimeSolver(Board& board);
        void time(Solver* pSolver, bool multiCore);
        Timer getTime() { return timer_; }
    private:
        Board board_;
        Timer timer_ = Timer();
};
