//
//  fileutil.hpp
//  dsafptest
//
//  Created by Zef on 4/19/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class File
{
private:
    string path;
public:
    File(string);
    string read();
    void write(string);
    void append(string);
};

#endif /* fileutil_hpp */


// Res: http://www.cplusplus.com/doc/tutorial/files/
