//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  timer.hpp
//  A class that handles method runtime tracking.
//

#ifndef timer_hpp
#define timer_hpp

#include <iostream>
#include <chrono>

using namespace std;

struct Timer
{
    string name;
    chrono::time_point<chrono::steady_clock> start, end;
    chrono::duration<double> duration;
    Timer(string name);
    ~Timer();
};

#endif