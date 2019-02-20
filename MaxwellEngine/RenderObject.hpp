//
//  RenderObject.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef RenderObject_hpp
#define RenderObject_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
#include "mes.h"

class mes::RenderObject
{
private:
    unsigned int VAO, VBO, EBO, EBO_size;
    std::unique_ptr<mes::TextureObject> texture_uptr;
    
public:
    RenderObject()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }
    
    template<class T>
    void init(mes::VertexDataObject<T>& vdo, unsigned int indices[], size_t indicesSize);
    void addTexture(const mes::TextureObject& textureObject);
    
    void render();
};

#endif /* RenderObject_hpp */
