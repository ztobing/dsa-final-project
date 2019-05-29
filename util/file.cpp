//
//  fileutil.cpp
//  dsafptest
//
//  Created by Zef on 4/19/19.
//  Copyright © 2019 zefryuuko. All rights reserved.
//

#include "file.hpp"

File::File(string path)
{
    this->path = path;
}

string File::read()
{
    ifstream fs(this->path);
    string lineBuffer;
    string contentBuffer = "";
    
    if (!fs.is_open())
    {
        cerr << "FailedToOpen" << " " << this->path << endl;
        exit(1);
    }
    
    while(getline(fs, lineBuffer))
    {
        contentBuffer += lineBuffer + "\n";
    }
    
    contentBuffer = contentBuffer.substr(0, contentBuffer.size() - 1);
    fs.close();
    return contentBuffer;
}

void File::write(string data)
{
    ofstream fs(this->path);
    fs << data << "\n";
    fs.close();
}

void File::append(string data)
{
    this->write(this->read() + "\n" + data);
}
