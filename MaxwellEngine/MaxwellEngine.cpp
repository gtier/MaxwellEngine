//
//  MaxwellEngine.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include "MaxwellEngine.hpp"

void mes::MaxwellEngine::init(int width, int height,  const char* vertShader, const char* fragmentShader)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); //This line is required for mac computers
    engineWindow = glfwCreateWindow(width, height, "MaxwellEngine", NULL, NULL);
    
    if (engineWindow == NULL) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        throw "Failed to create GLFW window!";
    }
    
    glfwMakeContextCurrent(engineWindow);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Get OS specific functions
    {
        std::cerr << "Failed to init GLAD!" << std::endl;
        throw "Failed to init GLAD!";
    }
    
    glViewport(0, 0, width, height);
    
    glfwSetFramebufferSizeCallback(engineWindow, frame_resize);
    
    engineVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(engineVertexShader, 1, &vertShader, NULL);
    glCompileShader(engineVertexShader);
    
    int compileSuccess;
    char compileInfoLog[512];
    glGetShaderiv(engineVertexShader, GL_COMPILE_STATUS, &compileSuccess);
    
    if (!compileSuccess)
    {
        glGetShaderInfoLog(engineVertexShader, 512, NULL, compileInfoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << compileInfoLog << std::endl;
        throw "ERROR::SHADER::VERTEX::COMPILATION_FAILED";
    }
    
    engineFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(engineFragmentShader, 1, &fragmentShader, NULL);
    glCompileShader(engineFragmentShader);
    
    glGetShaderiv(engineFragmentShader, GL_COMPILE_STATUS, &compileSuccess);
    
    if (!compileSuccess)
    {
        glGetShaderInfoLog(engineFragmentShader, 512, NULL, compileInfoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << compileInfoLog << std::endl;
        throw "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED";
    }
    
    engineShaderProgram = glCreateProgram();
    glAttachShader(engineShaderProgram, engineVertexShader);
    glAttachShader(engineShaderProgram, engineFragmentShader);
    glLinkProgram(engineShaderProgram);
    
    int linkSuccess;
    char linkInfoLog[512];
    glGetProgramiv(engineShaderProgram, GL_LINK_STATUS, &linkSuccess);
    
    if (!linkSuccess)
    {
        glGetProgramInfoLog(engineShaderProgram, 512, NULL, linkInfoLog);
        std::cerr <<  "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << linkInfoLog << std::endl;
        throw  "ERROR::SHADER::PROGRAM::LINK_FAILED";
    }
    
    //Sets the OpenGL shader program to the inputted object. Pass in 0 to set the OpenGL shader program to the default program.
    glUseProgram(engineShaderProgram);
    
    glDeleteShader(engineVertexShader);
    glDeleteShader(engineFragmentShader);
}

void mes::MaxwellEngine::createRenderObject(std::vector<float>& verts, std::vector<unsigned int>& indices)
{
    size_t vertsSize = verts.size();
    size_t indicesSize = indices.size();
    
    float* vertsArr = &verts[0];
    unsigned int* indicesArr = &indices[0];
    
    std::unique_ptr<mes::RenderObject> renderObjectPointer = std::make_unique<mes::RenderObject>();
    renderObjectPointer->init(vertsArr, vertsSize * sizeof(float), indicesArr, indicesSize * sizeof(int));
    
    vecRenderObject.push_back(std::move(renderObjectPointer));
};

void mes::MaxwellEngine::startRenderLoop()
{
    while(!glfwWindowShouldClose(engineWindow))
    {
        //User Input
        
        //Rendering
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Sets the color of the clear (fills the entire buffer with this color)
        glClear(GL_COLOR_BUFFER_BIT); //Uses the OpenGL state clear color to clear the screen
        
        for (int i = 0; i < vecRenderObject.size(); ++i)
        {
            vecRenderObject[i]->render();
        }
        
        //Swap back buffer with front buffer (displayed image)
        glfwSwapBuffers(engineWindow);
        //Check events (Keyboard pressed or mouse movement)
        glfwPollEvents();
    }
}

void mes::MaxwellEngine::stopRenderLoop()
{
    glfwSetWindowShouldClose(engineWindow, GLFW_TRUE);
}