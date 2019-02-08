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

int main(int argc, const char * argv[]) {
    
    mes::ShaderFile vertexShaderFile("/Users/griffin/Documents/cpp-projects/MaxwellEngine/MaxwellEngine/Shaders/vertexShader.txt");
    
    mes::ShaderFile fragmentShaderFile("/Users/griffin/Documents/cpp-projects/MaxwellEngine/MaxwellEngine/Shaders/fragmentShader.txt");
    
    mes::MaxwellEngine engine(vertexShaderFile.read(), fragmentShaderFile.read());
    
    std::vector<float> verts1 = {
        -0.1, 0, 0,
        -0.5, 0.5, 0,
        -0.1, 0.5, 0
    };
    
    std::vector<unsigned int> indices1 = {
        0,1,2
    };
    
    std::vector<float> verts2 = {
        0.1, 0, 0,
        0.5, 0.5, 0,
        0.1, 0.5, 0
    };
    
    std::vector<unsigned int> indices2 = {
        0,1,2
    };
    
    engine.createRenderObject(verts1, indices1);
    engine.createRenderObject(verts2, indices2);
    engine.startRenderLoop();
    return 0;
}