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
        cout << recursive(start + spacing, start, spacing) << endl;

    // Right wall
    else if (map[start + 1] == '\n')
        cout << recursive(start - 1, start, spacing) << endl;

    // Bottom wall
    else if (start > map.length() - spacing && start < map.length())
        cout << recursive(start - spacing, start, spacing) << endl;

    // Left wall
    else if (start % spacing == 0)
        cout << recursive(start + 1, start, spacing) << endl;

    // Temp
    cout << map << endl;
}

bool Recursive::recursive(int index, int lastIndex, int spacing)
{
    // Base case
    if (index < 0) return false;
    if (index > map.length()) return false;
    if (map[index] == '1') return false;
    if (map[index] == '3') return true;

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
