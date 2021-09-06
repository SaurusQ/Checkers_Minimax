
#include "timer.hpp"

void Timer::start()
{
    running_ = true;
    std::cout << "TIMER start" << std::endl;
    start_ = std::chrono::high_resolution_clock::now();
}

void Timer::end()
{
    end_ = std::chrono::high_resolution_clock::now();
    std::cout << "TIMER end" << std::endl;
    valid_ = true;
    running_ = false;
}

void Timer::measureFunc(void (*func)())
{
    this->start();
    func();
    this->end();
}

void Timer::measureFunc(std::function<void()> const& lambda)
{
    this->start();
    lambda();
    this->end();
}

void Timer::print(Res resolution) const
{
    std::string end;
    uint64_t cnt;
    switch(resolution)
    {
        case Res::S:
            cnt = this->getS();
            end = "(S)";
            break;
        case Res::MS:
            cnt = this->getMs();
            end = "(MS)";
            break;
        case Res::US:
            cnt = this->getUs();
            end = "(US)";
            break;
        case Res::NS:
            cnt = this->getNs();
            end = "(NS)";
            break;
    }
    std::cout << "TIMER time: " << cnt << " " << end << std::endl;
}

uint64_t Timer::getS() const
{
    if(this->isValid())
        return std::chrono::duration_cast<std::chrono::seconds>(end_- start_).count();
    return 0;
}

uint64_t Timer::getMs() const
{
    if(this->isValid())
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_- start_).count();
    return 0;
}

uint64_t Timer::getUs() const
{
    if(this->isValid())
        return std::chrono::duration_cast<std::chrono::microseconds>(end_- start_).count();
    return 0;
}

uint64_t Timer::getNs() const
{
    if(this->isValid())
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_- start_).count();
    return 0;
}

bool Timer::isValid() const
{
    if(running_)
        std::cout << "ERR: Timer is running" << std::endl;
    if(!valid_)
        std::cout << "ERR: Timer has no valid time" << std::endl;
    return !running_ && valid_;
}

TimeSolver::TimeSolver(Board& board)
    : board_(board)
{
    
}

void TimeSolver::time(Solver* pSolver, bool multiCore)
{
    Board b = board_;
    timer_.measureFunc([&]{
        pSolver->evaluateBestMove(b, IS_BLACK, multiCore);
    });
}
