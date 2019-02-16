//
//  RenderObject.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include "RenderObject.hpp"

template <class T>
void mes::RenderObject::init(mes::VertexDataObject<T>& vdo, unsigned int indices[], size_t indicesSize)
{
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vdo.getSize(), vdo.getVertexArray(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    
    std::vector<mes::VertexAttribute> vertexAttributeList;
    vdo.createVertexAttributeList(vertexAttributeList);
    for (int i = 0; i < vertexAttributeList.size(); ++i)
    {
        glVertexAttribPointer(vertexAttributeList.at(i).location, vertexAttributeList.at(i).dimmension, vertexAttributeList.at(i).type, vertexAttributeList.at(i).normalized, vertexAttributeList.at(i).stride, vertexAttributeList.at(i).offset);
        glEnableVertexAttribArray(vertexAttributeList.at(i).location);
    }
    
    glBindVertexArray(0);
    
    EBO_size = static_cast<unsigned int>(indicesSize / sizeof(unsigned int));
}

//init templates
template void mes::RenderObject::init<float>(mes::VertexDataObject<float>&, unsigned int indices[], size_t);

template void mes::RenderObject::init<int>(mes::VertexDataObject<int>&, unsigned int indices[], size_t);

template void mes::RenderObject::init<double>(mes::VertexDataObject<double>&, unsigned int indices[], size_t);

void mes::RenderObject::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, EBO_size, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
