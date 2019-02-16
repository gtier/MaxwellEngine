//
//  Vec.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/14/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef Vec_hpp
#define Vec_hpp

#include <stdio.h>
#include <type_traits>
#include <iostream>
#include <memory>

namespace mes {
    template <class T, int dimmension>
    class Vec
    {
    public:
        T data[dimmension] = {};
        const int dim;
        
        Vec()
        : dim(dimmension)
        {
        }
        
        Vec(T* vals)
        : dim(dimmension)
        {
            for(int i = 0; i < dimmension; ++i)
            {
                data[i] = vals[i];
            }
        }
        
        Vec(const Vec<T, dimmension>& vecToCopy)
        : dim(vecToCopy.dim)
        {
            for (int i = 0; i < dim; ++i)
            {
                data[i] = vecToCopy.data[i];
            }
        }
        
        size_t getSize()
        {
            return dim * sizeof(T);
        }
        
        int getDimmension()
        {
            return dim;
        }
        
        void operator+=(const Vec<T, dimmension>& vecToAdd)
        {
            if (dim != vecToAdd.dim) {
                throw "Vectors must be of the same dimmension";
            }
            for (int i = 0; i < dim; ++i)
            {
                data[i] += vecToAdd.data[i];
            }
        }
        
        void operator-=(const Vec<T, dimmension>& vecToSubtract)
        {
            if (dim != vecToSubtract.dim) {
                throw "Vectors must be of the same dimmension";
            }
            for (int i = 0; i < dim; ++i)
            {
                data[i] -= vecToSubtract.data[i];
            }
        }
        
        Vec<T, dimmension> operator+(const Vec<T, dimmension>& vecToAdd)
        {
            if (dim != vecToAdd.dim) {
                throw "Vectors must be of the same dimmension";
            }
            Vec<T, dimmension> temp;
            temp = *this;
            for (int i = 0; i < dim; ++i)
            {
                temp.data[i] += vecToAdd.data[i];
            }
            return temp;
        }
        
        Vec<T, dimmension> operator-(const Vec<T, dimmension>& vecToSubtract)
        {
            if (dim != vecToSubtract.dim) {
                throw "Vectors must be of the same dimmension";
            }            Vec<T, dimmension> temp;
            temp = *this;
            for (int i = 0; i < dim; ++i)
            {
                temp.data[i] -= vecToSubtract.data[i];
            }
            return temp;
        }
        
        Vec<T, dimmension>& operator=(const Vec<T, dimmension>& vecToAssign)
        {
            if (dim != vecToAssign.dim) {
                throw "Vectors must be of the same dimmension";
            }
            if (this != &vecToAssign)
            {
                for (int i = 0; i < dim; ++i)
                {
                    data[i] = vecToAssign.data[i];
                }
            }
            return *this;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Vec<T, dimmension>& outVec)
        {
            for (int i = 0; i < outVec.dim; ++i)
            {
                if (i == 0) {
                    os << "(" << outVec.data[i] << ",";
                } else if (i < outVec.dim - 1) {
                    os << outVec.data[i] << ",";
                } else {
                    os << outVec.data[i] << ")";
                }
            }
            
            return os;
        }
        
    };
    
    typedef Vec<int, 2> Vec2i;
    typedef Vec<float, 2> Vec2f;
    typedef Vec<double, 2>Vec2d;
    
    typedef Vec<int, 3> Vec3i;
    typedef Vec<float, 3> Vec3f;
    typedef Vec<double, 3> Vec3d;
    
    typedef Vec<int, 4> Vec4i;
    typedef Vec<float, 4> Vec4f;
    typedef Vec<double, 4> Vec4d;
    
    template <class T>
    T createVec()
    {
        static_assert(std::is_same<T, Vec2i>::value || std::is_same<T, Vec2f>::value || std::is_same<T, Vec2d>::value || std::is_same<T, Vec3i>::value || std::is_same<T, Vec3f>::value || std::is_same<T, Vec3d>::value || std::is_same<T, Vec4i>::value || std::is_same<T, Vec4f>::value || std::is_same<T, Vec4d>::value, "A valid Vec template is required");
        
        return T();
    }
}

#endif /* Vec_hpp */
