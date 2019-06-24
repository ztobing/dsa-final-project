//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  mapreader.cpp
//  A class that handles maze map reading.
//  This class has methods for validation and calls for
//  the solving algorithm.
//

#include "mapreader.hpp"

MapReader::MapReader(string mapFile)
{
    this->start = this->end = this->spacing = -1;
    this->height = 0;
    File f(mapFile);
    string mapData = f.read();
    if (validate(mapData)) this->raw = mapData;
    else
    {
        cerr << "InvalidMapFile" << endl;
        exit(1);
    }
}

bool MapReader::validate(const string &mapFile)
{
    for (int i = 0; i < mapFile.length(); i++)
    {
        if (mapFile[i] != '0' && mapFile[i] != '1' && mapFile[i] != '\n' && mapFile[i] != '2' && mapFile[i] != '3') return false;
        if (mapFile[i] == '0' || mapFile[i] == '1') continue;

        if (mapFile[i] == '\n') 
        {
            this->height++;
            if (this->spacing == -1)
            {
                this->spacing = i + 1;
                continue;
            }
            else continue;
        }

        if (mapFile[i] == '2' && this->start == -1) this->start = i;
        else if (mapFile[i] == '3' && this->end == -1) this->end = i;
        else return false;
    }
    if (this->start == -1 || this->end == -1) return false;

    return true;
}

bool MapReader::read(int algo)
{
    switch(algo)
    {
        case 1:
        {
            cout << "MAP_INFO: " << this->spacing << "x" << this->height << endl;
            cout << "ALGO: " << "Recursive" << endl;
            Recursive r(this->raw, this->start, this->end, this->spacing);
            r.run();
            break;
        }
        case 2:
        {
            cout << "MAP_INFO: " << this->spacing << "x" << this->height << endl;
            cout << "ALGO: " << "DFS" << endl;
            DFS d(this->raw, this->start, this->end, this->spacing);
            d.run();
            break;
        }
        case 3:
        {
            cout << "MAP_INFO: " << this->spacing << "x" << this->height << endl;
            cout << "ALGO: " << "BFS" << endl;
            BFS b(this->raw, this->start, this->end, this->spacing);
            b.run();
            break;
        }
        default:
        {
            cerr << "InvalidArgument" << endl;
            exit(1);
        }
    }
    return true;
}
