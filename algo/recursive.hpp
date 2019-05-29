//
//  Recursive.hpp
//  dsafptest
//
//  Created by Zef on 5/21/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
//

#ifndef recursive_hpp
#define recursive_hpp

#include <iostream>
#include "../util/timer.hpp"

using namespace std;

class Recursive
{
private:
    string map;
    int start, end, spacing;
    bool recursive(int index, int lastIndex, int spacing);
public:
    Recursive(string map, int start, int end, int spacing);
    void run();
};

#endif /* Recursive_hpp */
