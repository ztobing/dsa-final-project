//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  main.cpp
//  Handles command line interface
//

#include <iostream>
#include "util/file.hpp"
#include "util/timer.hpp"
#include "util/mapreader.hpp"

int main(int argc, const char * argv[])
{
    if (argc == 1)
    {
        cout << "Usage: maze <file> [algo]" << endl;
        cout << "Algo: 1. Recursive" << endl;
        cout << "      2. Depth First Search" << endl;
        cout << "      3. Breadth First Search" << endl;
        return 1;
    }
    if (argc >= 2)
    {
        MapReader m(argv[1]);
        if (argc >=3)
            // Read map with user specified algorithm
            m.read(argv[2][0] - 48);
        else
            // Read map with recursive algorithm if no algorithm parameter is passed.
            m.read(1);
    }
    
    return 0;
}
