//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  recursive.hpp
//  A solving implementation using recursive method.
//  This method works by checking the surrounding of the current
//  position and walk on every path possible until a solution is found.
//

#ifndef recursive_hpp
#define recursive_hpp

#include <iostream>
#include "../util/timer.hpp"
#include "../util/file.hpp"

using namespace std;

class Recursive
{
private:
    string map;
    int start, end, spacing;
    bool recursive(int index, int lastIndex, int spacing);
public:
    Recursive(string map, int start, int end, int spacing);
    void run();
};

#endif /* Recursive_hpp */
