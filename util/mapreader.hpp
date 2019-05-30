//
//  mapreader.hpp
//  dsafptest
//
//  Created by Zef on 4/26/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
//

#ifndef mapreader_hpp
#define mapreader_hpp

#include <iostream>
#include "file.hpp"
#include "timer.hpp"
#include "../algo/recursive.hpp"
#include "../algo/eagleeye.hpp"

using namespace std;

class MapReader
{
private:
    string raw;
    int start;
    int end;
    int spacing;
    bool validate(const string &);
public:
    MapReader(string);
    bool read(int algo);
    bool clearCache();
    long size();
};

#endif /* mapreader_hpp */