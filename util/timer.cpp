//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  timer.cpp
//  A class that handles method runtime tracking.
//

#include "timer.hpp"

Timer::Timer(string name)
{
    this->name = name;
    start = chrono::steady_clock::now();
}

Timer::~Timer()
{
    end = chrono::steady_clock::now();
    duration = end - start;
    
    double durationMs = duration.count() * 1000.0;
    cout << this->name + " took " << durationMs << "ms\n";
}
