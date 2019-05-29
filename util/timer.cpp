//
//  metrics.cpp
//  dsafptest
//
//  Created by Zef on 4/19/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
//

#include "timer.hpp"

Timer::Timer(string name)
{
    this->name = name;
    start = chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    
    double durationMs = duration.count() * 1000.0;
    cout << this->name + " took " << durationMs << "ms\n";
}
