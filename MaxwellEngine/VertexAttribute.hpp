//
//  VertexAttribute.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/15/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef VertexAttribute_hpp
#define VertexAttribute_hpp

#include <stdio.h>
#include <iostream>
#include "mes.h"

namespace mes {
    
    class VertexAttribute
    {
    public:
        const int location, dimmension, type, normalized, stride;
        const void* offset;
        VertexAttribute(int location, int dimmension, int type, int normalized, int stride, void* offset)
        : location(location), dimmension(dimmension), type(type), normalized(normalized), stride(stride),
        offset(offset)
        {
        }
        
        friend std::ostream& operator<<(std::ostream& os, const VertexAttribute& vertexAttribute)
        {
            os << "(" << vertexAttribute.location << "," << vertexAttribute.dimmension << "," << vertexAttribute.type << "," << vertexAttribute.normalized << "," << vertexAttribute.stride << "," << vertexAttribute.offset << ")";
            
            return os;
        };
    };
}

#endif /* VertexAttribute_hpp */
