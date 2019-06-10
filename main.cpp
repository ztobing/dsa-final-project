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

int main(int argc, const char * argv[]) {
    if (argc == 1)
    {
        cout << "Usage: maze <file> [algo]" << endl;
        return 1;
    }
    if (argc >= 2)
    {
        MapReader m(argv[1]);
        if (argc >=3)
            m.read(argv[2][0] - 48);
        else
            m.read(1);
    }
    
    return 0;
}
