//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  file.hpp
//  A class that handles file I/O process.
//  This class enables higher level file I/O methods to make things easier
//  while working with this project.
//

#ifndef file_hpp
#define file_hpp

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class File
{
private:
    string path;
public:
    File(string);
    string read();
    void write(string);
    void append(string);
};

#endif

// Resource: http://www.cplusplus.com/doc/tutorial/files/
