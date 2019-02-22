//
//  main.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MaxwellEngine.hpp"
#include "RenderObject.hpp"
#include "ShaderFile.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void renderIntercept(mes::MaxwellEngine& engine)
{
    engine.getRenderObject(0).setModelMatrix(glm::mat4(1.0f));
    engine.getRenderObject(0).setModelMatrix(glm::rotate(engine.getRenderObject(0).getModelMatrix(), (float)glfwGetTime(), glm::vec3(0.5f, -1.0f, 0.0f)));
}

int main(int argc, const char * argv[]) {
    mes::ShaderFile vertexShaderFile("/Users/griffin/Documents/cpp-projects/MaxwellEngine/MaxwellEngine/Shaders/vertexShader.glsl");
    
    mes::ShaderFile fragmentShaderFile("/Users/griffin/Documents/cpp-projects/MaxwellEngine/MaxwellEngine/Shaders/fragmentShader.glsl");
    
    mes::MaxwellEngine engine(vertexShaderFile.read(), fragmentShaderFile.read());
    
    std::vector<float> verts1 = {
        // positions          // colors           // texture coords
        1.0f,  1.0f, 1.0f, 1.0f, 1.0f, // top right
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  // top left
        
        1.0f,  1.0f, -1.0f, 1.0f, 1.0f, // top right
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,  // top left
        
        1.0f,  1.0f, -1.0f, 1.0f, 1.0f, // top right
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // bottom right
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  // top left
    };
    
    std::vector<unsigned int> indices1  = {
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
        
        4, 5, 7, // first triangle
        5, 6, 7,  // second triangle
        
        8, 9, 11, // first triangle
        9, 10, 11,  // second triangle
        
    };
    
    std::vector<float> verts2 = {
        0.1, 0, 0,
        0.5, 0.5, 0,
        0.1, 0.5, 0
    };
    
    std::vector<unsigned int> indices2 = {
        0,1,2
    };
    
    mes::VectorFloat_uptr verts1ptr(&verts1);
    mes::VDOFloat vdo1(verts1ptr);
    vdo1.addVertexType(mes::VDOFloat::VEC3);
    vdo1.addVertexType(mes::VDOFloat::VEC2);
    
    mes::VectorFloat_uptr verts2ptr(&verts2);
    mes::VDOFloat vdo2(verts2ptr);
    vdo2.addVertexType(mes::VDOFloat::VertexDataType::VEC3);
    
    mes::MaxwellEngine::obj_id id;
    id = engine.createRenderObject(vdo1, indices1);
   // engine.createRenderObject(vdo2, indices2);
    
    mes::TextureObject texture("/Users/griffin/Desktop/profile.jpg");
    engine.getRenderObject(id).addTexture(texture);
    
    engine.getMainCamera().setViewMatrix(glm::translate(engine.getMainCamera().getViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
    
    engine.startRenderLoop(renderIntercept);
    
    return 0;
}
