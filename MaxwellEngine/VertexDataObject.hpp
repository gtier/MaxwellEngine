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
#include <memory>

namespace mes {
    
    template <class T>
    class VertexDataObject
    {
    public:
        typedef std::unique_ptr<std::vector<T>> VertexDataPtr_t;
        
        enum VertexDataType {
            VEC2 = 2,
            VEC3 = 3,
            VEC4 = 4
        };
        
    private:
        VertexDataPtr_t vertexDataPtr;
        std::vector<VertexDataType> vertexTypes;
        
    public:
        VertexDataObject(VertexDataPtr_t& vertexDataPtr)
        : vertexDataPtr(std::move(vertexDataPtr))
        {
        }
        
        void addVertexData(const T& dataToAdd)
        {
            vertexDataPtr->push_back(dataToAdd);
        }
        
        void addVertexType(const VertexDataType& attribType)
        {
            vertexTypes.push_back(attribType);
        }
        
        std::vector<T>& getVertexData()
        {
            return *vertexDataPtr;
        }
        
        T* getVertexArray()
        {
            return &((*vertexDataPtr).at(0));
        }
        
        std::vector<VertexDataType>& getVertexTypes()
        {
            return vertexTypes;
        }
        
        int getStride()
        {
            int counter(0);
            for (int i = 0; i < vertexTypes.size(); ++i)
            {
                counter += vertexTypes.at(i) * sizeof(T);
            }
            return counter;
        }
        
        long getSize()
        {
            return vertexDataPtr->size() * sizeof(T);
        }
        void createVertexAttributeList(std::vector<VertexAttribute>& output)
        {
            output.clear();
            long offset(0);
            for (int i = 0; i < vertexTypes.size(); ++i)
            {
                if (i == 0) {
                    VertexAttribute tempVertexAttribute(i, vertexTypes.at(i), getGLenum(), GL_FALSE, getStride(), (void*)0);
                        output.push_back(tempVertexAttribute);
                } else {
                    offset += vertexTypes.at(i-1) * sizeof(T);
                    VertexAttribute tempVertexAttribute(i, vertexTypes.at(i), getGLenum(), GL_FALSE, getStride(), (void*)offset);
                    std::cout << "Test: " << offset << std::endl;
                    output.push_back(tempVertexAttribute);
                }
            }
        }
    private:
        int getGLenum() {
            if (std::is_same<T, float>::value) {
                return GL_FLOAT;
            } else if (std::is_same<T, int>::value) {
                return GL_INT;
            } else if (std::is_same<T, double>::value) {
                return GL_DOUBLE;
            } else {
                throw "Invalid VertexDataObject type. Must be float, int, or double";
            }
        }
    };
    
    template<class T>
    using VDO = VertexDataObject<T>;
    
    typedef VertexDataObject<float> VDOFloat;
    typedef VertexDataObject<int> VDOInt;
    typedef VertexDataObject<double> VDODouble;
}

#endif /* VertexDataObject_hpp */
