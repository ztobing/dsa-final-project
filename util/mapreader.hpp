//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  mapreader.hpp
//  A class that handles maze map reading.
//  This class has methods for validation and calls for
//  the solving algorithm.
//

#ifndef mapreader_hpp
#define mapreader_hpp

#include <iostream>
#include "file.hpp"
#include "timer.hpp"
#include "../algo/recursive.hpp"
#include "../algo/dfs.hpp"
#include "../algo/bfs.hpp"

using namespace std;

class MapReader
{
private:
    string raw;
    int start;
    int end;
    int spacing;
    bool validate(const string &);
public:
    MapReader(string);
    bool read(int algo);
    bool clearCache();
    long size();
};

#endif