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
    
    //IMPORTANT
    //Texture unit configuration: sets fragment shader uniform "customTexture" sampler to 0.
    glUniform1i(glGetUniformLocation(engineShaderProgram, "customTexture"), 0);
    
    glDeleteShader(engineVertexShader);
    glDeleteShader(engineFragmentShader);
}

template <class T>
mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject(mes::VertexDataObject<T>& vdo, std::vector<unsigned int>& indices)
{
    size_t indicesSize = indices.size();
    
    unsigned int* indicesArr = &indices[0];
    
    std::unique_ptr<mes::RenderObject> renderObjectPointer = std::make_unique<mes::RenderObject>();
    renderObjectPointer->init(vdo, indicesArr, indicesSize * sizeof(int));
    
    vecRenderObject.push_back(std::move(renderObjectPointer));
    
    return vecRenderObject.size() - 1;
};

//createRenderObject templates
template mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject<float>(mes::VertexDataObject<float>&, std::vector<unsigned int>&);

template mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject<int>(mes::VertexDataObject<int>&, std::vector<unsigned int>&);

template mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject<double>(mes::VertexDataObject<double>&, std::vector<unsigned int>&);


void mes::MaxwellEngine::startRenderLoop()
{
    renderLoop(nullptr, nullptr);
}

void mes::MaxwellEngine::startRenderLoop(handleInput_t handleInput)
{
    renderLoop(handleInput, nullptr);
}

void mes::MaxwellEngine::startRenderLoop(renderIntercept_t renderIntercept)
{
    renderLoop(nullptr, renderIntercept);
}

void mes::MaxwellEngine::startRenderLoop(handleInput_t handleInput, renderIntercept_t renderIntercept)
{
    renderLoop(handleInput, renderIntercept);
}

void mes::MaxwellEngine::renderLoop(void (*handleInput)(GLFWwindow* window), void (*renderIntercept)())
{
    while(!glfwWindowShouldClose(engineWindow))
    {
        //User Input
        if (handleInput)
        {
            handleInput(engineWindow);
        }
        //Rendering
        
        //Calling the render intercept
        if (renderIntercept)
        {
            renderIntercept();
        }
        
        renderFrame();
    }
}

void mes::MaxwellEngine::renderFrame()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

void mes::MaxwellEngine::stopRenderLoop()
{
    glfwSetWindowShouldClose(engineWindow, GLFW_TRUE);
}
