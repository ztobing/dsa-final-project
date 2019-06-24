//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  file.cpp
//  A class that handles file I/O process.
//  This class enables higher level file I/O methods to make things easier
//  while working with this project.
//

#include "file.hpp"

File::File(string path)
{
    this->path = path;
}

string File::read()
{
    ifstream fs(this->path);
    string lineBuffer;
    string contentBuffer = "";
    
    if (!fs.is_open())
    {
        cerr << "FailedToOpen" << " " << this->path << endl;
        exit(1);
    }
    
    while(getline(fs, lineBuffer))
    {
        contentBuffer += lineBuffer + "\n";
    }
    
    contentBuffer = contentBuffer.substr(0, contentBuffer.size() - 1);
    fs.close();
    return contentBuffer;
}

void File::write(string data)
{
    ofstream fs(this->path);
    fs << data;
    fs.close();
}

void File::append(string data)
{
    this->write(this->read() + "\n" + data);
}
