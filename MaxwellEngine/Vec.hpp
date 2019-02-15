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
    template <class T>
    class Vec
    {
    public:
        std::unique_ptr<T[]> data;
        int dim;
        
        Vec(int dimmension)
        {
            dim = dimmension;
            data = std::make_unique<T[]>(dimmension);
        }
        
        Vec(int dimmension, T* vals)
        {
            dim = dimmension;
            data = std::make_unique<T[]>(dimmension);
            for(int i = 0; i < dimmension; ++i)
            {
                data[i] = vals[i];
            }
        }
        
        Vec(const Vec<T>& vecToCopy)
        {
            static_assert(dim == vecToCopy.dim, "Vectors must be of the same dimmension");
            for (int i = 0; i < dim; ++i)
            {
                data[i] = vecToCopy.data[i];
            }
        }
        
        int getDimmension()
        {
            return dim;
        }
        
        void operator+=(const Vec<T>& vecToAdd)
        {
            static_assert(dim == vecToAdd.dim, "Vectors must be of the same dimmension");
            for (int i = 0; i < dim; ++i)
            {
                data[i] += vecToAdd.data[i];
            }
        }
        
        void operator-=(const Vec<T>& vecToSubtract)
        {
            static_assert(dim == vecToSubtract.dim, "Vectors must be of the same dimmension");
            for (int i = 0; i < dim; ++i)
            {
                data[i] -= vecToSubtract.data[i];
            }
        }
        
        Vec<T> operator+(const Vec<T>& vecToAdd)
        {
            static_assert(dim == vecToAdd.dim, "Vectors must be of the same dimmension");
            Vec<T> temp;
            temp = *this;
            for (int i = 0; i < dim; ++i)
            {
                temp.data[i] += vecToAdd.data[i];
            }
        }
        
        Vec<T> operator-(const Vec<T>& vecToSubtract)
        {
            static_assert(dim == vecToSubtract.dim, "Vectors must be of the same dimmension");
            Vec<T> temp;
            temp = *this;
            for (int i = 0; i < dim; ++i)
            {
                temp.data[i] -= vecToSubtract.data[i];
            }
        }
        
        Vec<T>& operator=(const Vec<T>& vecToAssign)
        {
            static_assert(dim == vecToAssign.dim, "Vectors must be of the same dimmension");
            if (this != &vecToAssign)
            {
                for (int i = 0; i < dim; ++i)
                {
                    data[i] = vecToAssign.data[i];
                }
            }
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Vec<T>& outVec)
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
        }
        
    };
    
    template <class T>
    class Vec2
    {
    public:
        T x, y;
        
        Vec2()
        : x(0), y(0)
        {
        }
        
        Vec2(T x, T y)
        : x(x), y(y)
        {
        }
        
        Vec2(const Vec2<T>& vecToCopy)
        {
            x = vecToCopy.x;
            y = vecToCopy.y;
        }
        
        int length()
        {
            return 2;
        }
        
        size_t getTypeHash()
        {
            return typeid(T).hash_code();
        }
        
        void operator+=(const Vec2<T>& vecToAdd)
        {
            x += vecToAdd.x;
            y += vecToAdd.y;
        }
        
        void operator-=(const Vec2<T>& vecToSubtract)
        {
            x -= vecToSubtract.x;
            y -= vecToSubtract.y;
        }
        
        Vec2<T> operator+(const Vec2<T>& vecToAdd)
        {
            Vec2<T> temp;
            temp = *this;
            temp.x += vecToAdd.x;
            temp.y += vecToAdd.y;
            return temp;
        }
        
        Vec2<T> operator-(const Vec2<T>& vecToSubtract)
        {
            Vec2<T> temp;
            temp = *this;
            temp.x -= vecToSubtract.x;
            temp.y -= vecToSubtract.y;
            return temp;
        }
        
        Vec2<T>& operator=(const Vec2<T>& vecToAssign)
        {
            if (this != &vecToAssign)
            {
                x = vecToAssign.x;
                y = vecToAssign.y;
            }
            
            return *this;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec2)
        {
            os << "(" << vec2.x << "," << vec2.y << ")";
            return os;
        }
    };
    
    template <class T>
    class Vec3
    {
    public:
        T x, y, z;
        
        Vec3()
        : x(0), y(0), z(0)
        {
        }
        
        Vec3(T x, T y, T z)
        : x(x), y(y), z(z)
        {
        }
        
        Vec3(const Vec3<T>& vecToCopy)
        {
            x = vecToCopy.x;
            y = vecToCopy.y;
            z = vecToCopy.z;
        }
        
        int length()
        {
            return 3;
        }
        
        size_t getTypeHash()
        {
            return typeid(T).hash_code();
        }
        
        void operator+=(const Vec3<T>& vecToAdd)
        {
            x += vecToAdd.x;
            y += vecToAdd.y;
            z += vecToAdd.z;
        }
        
        void operator-=(const Vec3<T>& vecToSubtract)
        {
            x -= vecToSubtract.x;
            y -= vecToSubtract.y;
            z -= vecToSubtract.z;
        }
        
        Vec3<T> operator+(const Vec3<T>& vecToAdd)
        {
            Vec3<T> temp;
            temp = *this;
            temp.x += vecToAdd.x;
            temp.y += vecToAdd.y;
            temp.z += vecToAdd.z;
            return temp;
        }
        
        Vec3<T> operator-(const Vec3<T>& vecToSubtract)
        {
            Vec3<T> temp;
            temp = *this;
            temp.x -= vecToSubtract.x;
            temp.y -= vecToSubtract.y;
            temp.z -= vecToSubtract.z;
            return temp;
        }
        
        Vec3<T>& operator=(const Vec3<T>& vecToAssign)
        {
            if (this != &vecToAssign)
            {
                x = vecToAssign.x;
                y = vecToAssign.y;
                z = vecToAssign.z;
            }
            
            return *this;
        }
        
        
        friend std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec3)
        {
            os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
            return os;
        }
    };
   
    
    template <class T>
    class Vec4
    {
    public:
        T x, y, z, w;
        
        Vec4()
        : x(0), y(0), z(0), w(0)
        {
        }
        
        Vec4(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
        {
        }
        
        Vec4(const Vec4<T>& vecToCopy)
        {
            x = vecToCopy.x;
            y = vecToCopy.y;
            z = vecToCopy.z;
            w = vecToCopy.w;
        }
        
        int length()
        {
            return 4;
        }
        
        size_t getTypeHash()
        {
            return typeid(T).hash_code();
        }
        
        void operator+=(const Vec4<T>& vecToAdd)
        {
            x += vecToAdd.x;
            y += vecToAdd.y;
            z += vecToAdd.z;
            w += vecToAdd.w;
        }
        
        void operator-=(const Vec4<T>& vecToSubtract)
        {
            x -= vecToSubtract.x;
            y -= vecToSubtract.y;
            z -= vecToSubtract.z;
            w -= vecToSubtract.w;
        }
        
        Vec4<T> operator+(const Vec4<T>& vecToAdd)
        {
            Vec4<T> temp;
            temp = *this;
            temp.x += vecToAdd.x;
            temp.y += vecToAdd.y;
            temp.z += vecToAdd.z;
            temp.w += vecToAdd.w;
            return temp;
        }
        
        Vec4<T> operator-(const Vec4<T>& vecToSubtract)
        {
            Vec4<T> temp;
            temp = *this;
            temp.x -= vecToSubtract.x;
            temp.y -= vecToSubtract.y;
            temp.z -= vecToSubtract.z;
            temp.w -= vecToSubtract.w;
            return temp;
        }
        
        Vec4<T>& operator=(const Vec4<T>& vecToAssign)
        {
            if (this != &vecToAssign)
            {
                x = vecToAssign.x;
                y = vecToAssign.y;
                z = vecToAssign.z;
                w = vecToAssign.w;
            }
            
            return *this;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Vec4<T>& vec4)
        {
            os << "(" << vec4.x << "," << vec4.y << "," << vec4.z << "," << vec4.w << ")";
            return os;
        }
    };
    
    typedef Vec2<int> Vec2i;
    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;
    
    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
    
    typedef Vec4<int> Vec4i;
    typedef Vec4<float> Vec4f;
    typedef Vec4<double> Vec4d;
    
    template <class T>
    T createVec()
    {
        static_assert(std::is_same<T, Vec2i>::value || std::is_same<T, Vec2f>::value || std::is_same<T, Vec2d>::value || std::is_same<T, Vec3i>::value || std::is_same<T, Vec3f>::value || std::is_same<T, Vec3d>::value || std::is_same<T, Vec4i>::value || std::is_same<T, Vec4f>::value || std::is_same<T, Vec4d>::value, "A valid Vec template is required");
        
        return T();
    }
}

#endif /* Vec_hpp */
