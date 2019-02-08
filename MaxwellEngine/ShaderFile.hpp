//
//  ShaderFile.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/7/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef ShaderFile_hpp
#define ShaderFile_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include "mes.h"

class mes::ShaderFile
{
private:
    std::ifstream file;
    std::string path;
    std::unique_ptr<std::string> data_ptr;
    
public:
    ShaderFile(std::string path)
    : path(path)
    {
    }
    
    const char *  read();
};



#endif /* ShaderFile_hpp */
