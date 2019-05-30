//
//  Recursive.cpp
//  dsafptest
//
//  Created by Zef on 5/21/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
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
    
    // Top wall
    if (start < spacing)
        recursive(start + spacing, start, spacing);

    // Right wall
    else if (map[start + 1] == '\n')
        recursive(start - 1, start, spacing);

    // Bottom wall
    else if (start > map.length() - spacing && start < map.length())
        recursive(start - spacing, start, spacing);

    // Left wall
    else if (start % spacing == 0)
        recursive(start + 1, start, spacing);

    // Temp
    for (int i = 0; i < map.length(); i++)
    {
        if (map[i] == '5') map[i] = '0';
    }
    cout << map << endl;
}

// left hand recursion
bool Recursive::recursive(int index, int lastIndex, int spacing)
{
    // Base case
    if (index < 0) return false;
    if (index > map.length()) return false;
    if (map[index] == '1') return false;
    if (map[index] == '3') return true;
    if (map[index] == '5') return false;
    map[index] = '5';

    // Move left
    if (index - 1 != lastIndex)
        if (recursive(index - 1, index, spacing))
        {
            map[index] = '4';
            return true;
        }

    // Move right
    if (index + 1 != lastIndex)
        if (recursive(index + 1, index, spacing))
        {
            map[index] = '4';
            return true;
        }

    // Move down
    if (index + spacing != lastIndex)
        if (recursive(index + spacing, index, spacing))
        {
            map[index] = '4';
            return true;
        }

    // Move up
    if (index - spacing != lastIndex)
        if (recursive(index - spacing, index, spacing))
        {
            map[index] = '4';
            return true;
        }

    // If none worked
    return false;

}
