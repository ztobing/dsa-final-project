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
    this->start = this->end = this->spacing = -1;       // Set initial value to -1 to determine if the inital value has been changed on the validation method
    this->height = 0;
    File f(mapFile);
    string mapData = f.read();                          // Read the passed file
    if (validate(mapData)) this->raw = mapData;         // Validate the map before proceeding
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
        if (mapFile[i] == '\n') 
        {
            if (this->spacing == -1)                                // Check if width value had been set
            {
                this->spacing = i + 1;                          // Set width value for the first time
                break;
            }
        }
    }

    for (int i = 0; i < mapFile.length(); i++)
    {
        if (mapFile[i] != '0' && mapFile[i] != '1' && mapFile[i] != '2' && mapFile[i] != '3' && mapFile[i] != '\n') return false;   // Check if current char is a valid input character
        if (mapFile[i] == '0' || mapFile[i] == '1') continue;   // Continue checking if character is 1 or 0

        if (mapFile[i] == '\n') 
        {
            this->height++;
            continue;
        }

        if (mapFile[i] == '2' && this->start == -1) this->start = i;    // If character equals to 2 and it has never been set before
        else if (mapFile[i] == '3' && this->end == -1) this->end = i;   // If character equals to 3 and it has never been set before
        else return false;                                              // Return false if both conditions returns false
    }
    if (this->start == -1 || this->end == -1) return false;

    return true;
}

bool MapReader::read(int algo)
{
    switch(algo)
    {
        case 1:     // Recursive
        {
            cout << "MAP_INFO: " << this->spacing << "x" << this->height << endl;
            cout << "ALGO: " << "Recursive" << endl;
            Recursive r(this->raw, this->start, this->end, this->spacing);
            r.run();
            break;
        }
        case 2:     // Depth First Search
        {
            cout << "MAP_INFO: " << this->spacing << "x" << this->height << endl;
            cout << "ALGO: " << "DFS" << endl;
            DFS d(this->raw, this->start, this->end, this->spacing);
            d.run();
            break;
        }
        case 3:     // Breadth First Search
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
