//
//  metrics.hpp
//  dsafptest
//
//  Created by Zef on 4/19/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <iostream>
#include <chrono>

using namespace std;

struct Timer
{
    string name;
    chrono::time_point<chrono::steady_clock> start, end;
    chrono::duration<double> duration;
    Timer(string name);
    ~Timer();
};

#endif /* timer */