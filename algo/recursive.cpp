//
//  Maze Solver
//  ----------------------------------
//  Salya Wirachman - 2201798143
//  Zefanya Gedalya B.L.T - 2201796970
//  ----------------------------------
//  recursive.cpp
//  A solving implementation using recursive method.
//  This method works by checking the surrounding of the current
//  position and walk on every path possible until a solution is found.
//

#include "recursive.hpp"

Recursive::Recursive(string map, int start, int end, int spacing)
{
    this->map = map;
    this->start = start;
    this->end = end;
    this->spacing = spacing;
}

void Recursive::run()
{
    Timer t("Recursive");
    bool isSolved = false;

    // Determine starting position and run the algorithm based on the location.

    // Check top wall
    if (start < spacing)
        isSolved = recursive(start + spacing, start, spacing);

    // Check right wall
    else if (map[start + 1] == '\n')
        isSolved = recursive(start - 1, start, spacing);

    // Check bottom wall
    else if (start > map.length() - spacing && start < map.length())
        isSolved = recursive(start - spacing, start, spacing);

    // Check left wall
    else if (start % spacing == 0)
        isSolved = recursive(start + 1, start, spacing);

    cout << "STATUS: " << (isSolved ? "SOLVED" : "NO PATH") << endl;
    cout << map << endl;
}

bool Recursive::recursive(int index, int lastIndex, int spacing)
{
    // Base case
    if (index < 0) return false;                // Return false if index is less than 0
    if (index > map.length()) return false;     // Return false if index is out of bounds
    if (map[index] == '1') return false;        // Return false if current index points to a wall
    if (map[index] == '3') return true;         // Return true if current index poitns to the exit
    if (map[index] == '5') return false;        // Return false if current index points to a visited box
    map[index] = '5';                           // Set the current index to visited

    // Move left
    if (index - 1 != lastIndex)
        if (recursive(index - 1, index, spacing))
        {
            map[index] = '4';                   // Set the current index as the correct path
            return true;
        }

    // Move right
    if (index + 1 != lastIndex)
        if (recursive(index + 1, index, spacing))
        {
            map[index] = '4';                   // Set the current index as the correct path
            return true;
        }

    // Move down
    if (index + spacing != lastIndex)
        if (recursive(index + spacing, index, spacing))
        {
            map[index] = '4';                   // Set the current index as the correct path
            return true;
        }

    // Move up
    if (index - spacing != lastIndex)
        if (recursive(index - spacing, index, spacing))
        {
            map[index] = '4';                   // Set the current index as the correct path
            return true;
        }

    return false;                               // If none of the above returns true, return false

}
