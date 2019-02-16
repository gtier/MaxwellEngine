//
//  MaxwellEngine.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef MaxwellEngine_hpp
#define MaxwellEngine_hpp

#include <stdio.h>
#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include "mes.h"
#include "RenderObject.hpp"

class mes::MaxwellEngine
{
public:
    typedef std::vector<std::unique_ptr<mes::RenderObject>> VecRenderObject;
    typedef void (*renderIntercept_t)();
    typedef void (*handleInput_t)(GLFWwindow* window);
    
private:
    GLFWwindow* engineWindow;
    unsigned int engineVertexShader, engineFragmentShader, engineShaderProgram;
    VecRenderObject vecRenderObject;
    
public:
    MaxwellEngine(const char* vertShader, const char* fragmentShader)
    {
        init(800, 600, vertShader, fragmentShader);
    }
    
    MaxwellEngine(int width, int height, const char* vertShader, const char* fragmentShader)
    {
        init(width, height, vertShader, fragmentShader);
    }
    
    static void frame_resize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    
    template <class T>
    void createRenderObject(mes::VertexDataObject<T>& verts, std::vector<unsigned int>& indices);
    
    void startRenderLoop();
    
    void startRenderLoop(handleInput_t);
    
    void startRenderLoop(renderIntercept_t);
    
    void startRenderLoop(handleInput_t, renderIntercept_t);
    
    void stopRenderLoop();
    
private:
    void init(int width, int height, const char* vertShader, const char* fragmentShader);
    
    void renderLoop(void (*handleInput)(GLFWwindow* window), void (*renderIntercept)());
    
    void renderFrame();
};


#endif /* MaxwellEngine_hpp */
