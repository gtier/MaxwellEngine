//
//  VertexDataObject.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/14/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef VertexDataObject_hpp
#define VertexDataObject_hpp

#include <stdio.h>
#include "mes.h"
#include <iostream>
#include <vector>
#include <type_traits>

namespace mes {
    template <class T>
    class VertexDataObject
    {
    public:
        typedef Vec3<T> coord_t;
        typedef Vec3<T> color_t;
        typedef Vec2<T> uv_t;
    private:
        coord_t coord;
        color_t color;
        uv_t uv;
    public:
        VertexDataObject()
        {
        }
        
        
        VertexDataObject(const coord_t& coord, const color_t& color, const uv_t& uv)
        : coord(coord), color(color), uv(uv)
        {
        }
        
        
        friend std::ostream& operator<<(std::ostream& os, const VertexDataObject<T>& vdo)
        {
            os << "{" << vdo.coord << "," << vdo.color << "," << vdo.uv << "}";
            return os;
        }
        
        size_t coordSize()
        {
            return sizeof(coord);
        }
        
        size_t colorSize()
        {
            return sizeof(color);
        }
        
        size_t uvSize()
        {
            return sizeof(uv);
        }
        
        
    };
    
    template<class T>
    using VDO = VertexDataObject<T>;
    
    template<class T>
    using VectorVDO_t = std::vector<VertexDataObject<T> >;
    
    template<class T>
    class VectorVDO
    {
    private:
        VectorVDO_t<T> vectorVDO;
       
    public:
        VectorVDO()
        {
        }
        
        VectorVDO_t<T>& getVector() {
            return vectorVDO;
        }
    };
}

#endif /* VertexDataObject_hpp */
