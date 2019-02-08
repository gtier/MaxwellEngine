//
//  ShaderFile.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/7/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include "ShaderFile.hpp"

const char * mes::ShaderFile::read()
{
    file.open(path);
    std::stringstream stringStream;
    stringStream << file.rdbuf();
    file.close();
    data_ptr = std::make_unique<std::string>(stringStream.str());
    return data_ptr->c_str();
}
