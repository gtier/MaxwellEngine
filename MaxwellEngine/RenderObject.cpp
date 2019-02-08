//
//  RenderObject.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include "RenderObject.hpp"

void mes::RenderObject::init(float verts[], size_t vertsSize, unsigned int indices[], size_t indicesSize)
{
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertsSize, verts, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    
    EBO_size = static_cast<unsigned int>(indicesSize / sizeof(unsigned int));
}

void mes::RenderObject::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, EBO_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
