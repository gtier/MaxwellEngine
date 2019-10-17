//
//  MaxwellEngine.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include "MaxwellEngine.hpp"

static mes::CameraObject* staticCameraPtr = nullptr;

void mes::MaxwellEngine::init(int width, int height,  mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader)
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
    
    
    obj_id id = this->createShaderProgram(vertShader, fragmentShader);
    std::cout << "Shader vecID: " << id << std::endl;
    
    std::cout << "Build: " << vecShaderProgram[id]->build() << std::endl;
    
    std::cout << "Shader ID: " << vecShaderProgram[id]->getId() << std::endl;
    
    //Must be set after build
    engineShaderProgram = vecShaderProgram[id]->getId();
    
    //FIX BROKEN. I THINK THIS WORKS
    vecShaderProgram[id]->use();
    
    //Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    
    //IMPORTANT
    //Texture unit configuration: sets fragment shader uniform "customTexture" sampler to 0.
    vecShaderProgram[id]->setUniform("user_texture_0", glUniform1i, 0);
    //Texture unit configuration.
    
    //CONFIG: Mouse input configuration
    glfwSetInputMode(engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
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
    
    obj_id newId(0);
    
    if(emptyQueue.empty()) {
        vecRenderObject.push_back(std::move(renderObjectPointer));
        newId = vecRenderObject.size() - 1;
    } else {
        newId = emptyQueue.front();
        vecRenderObject[newId] = std::move(renderObjectPointer);
        emptyQueue.pop();
    }
    
    return newId;
};

//createRenderObject templates
template mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject<float>(mes::VertexDataObject<float>&, std::vector<unsigned int>&);

template mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject<int>(mes::VertexDataObject<int>&, std::vector<unsigned int>&);

template mes::MaxwellEngine::obj_id mes::MaxwellEngine::createRenderObject<double>(mes::VertexDataObject<double>&, std::vector<unsigned int>&);

void mes::MaxwellEngine::deleteRenderObject(const obj_id id)
{
    vecRenderObject[id] = nullptr;
    emptyQueue.push(id);
}

mes::MaxwellEngine::obj_id mes::MaxwellEngine::createShaderProgram(mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader)
{
    std::unique_ptr<mes::ShaderProgram> shaderProgram_ptr = std::make_unique<mes::ShaderProgram>(vertShader, fragmentShader);
    vecShaderProgram.push_back(std::move(shaderProgram_ptr));
    return vecShaderProgram.size() - 1;
}

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

void mes::MaxwellEngine::renderLoop(handleInput_t handleInput, renderIntercept_t renderIntercept)
{
    while(!glfwWindowShouldClose(engineWindow))
    {
        //Compute time delta
        currFrameTime = glfwGetTime();
        deltaFrameTime = currFrameTime - lastFrameTime;
        lastFrameTime = currFrameTime;
        
        //User Input
        if (toHandleInput)
        {
            handleInput(engineWindow);
        }
        
        //Rendering
        
        //Calling the render intercept
        if (renderIntercept)
        {
            renderIntercept(*this);
        }
        
        //TODO make a command queue
        
        renderFrame();
    }
}

void mes::MaxwellEngine::renderFrame()
{
    //Get user input
    if (cameraIsInputHandler) {
        mainCamera.keyHandler(engineWindow, deltaFrameTime);
    };
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //Binary OR operator used below
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Uses the OpenGL state clear color to clear the screen and clears the depth buffer
    
    for (int i = 0; i < vecRenderObject.size(); ++i)
    {
        //TODO create null RenderObject to get rid of if statement
        if (vecRenderObject[i])
        {
          vecRenderObject[i]->render(engineShaderProgram, mainCamera);
        }
    }
    
    //Swap back buffer with front buffer (displayed image)
    glfwSwapBuffers(engineWindow);
    //Check events (Keyboard pressed or mouse movement)
    glfwPollEvents();
}

//TODO delete this?
void mes::MaxwellEngine::addInputHandler(const handleInput_t& handler)
{
    if (!toHandleInput) {
        toHandleInput = true;
    }
    vecHandleInput.push_back(handler);
}

void mes::MaxwellEngine::cursorHandler(GLFWwindow *window, double x, double y)
{
    if (staticCameraPtr) {
        staticCameraPtr->cursorHandler(window, x, y);
    }
}

//TODO look at hpp file for notes
void mes::MaxwellEngine::mountStaticCamera()
{
    cameraIsInputHandler = true;
    cursorHandlerMounted = true;
    keyHandlerMounted = true;
    staticCameraPtr = &mainCamera;
}

void mes::MaxwellEngine::enableCursorHanler()
{
    handleCursorConfig = true;
    glfwSetCursorPosCallback(engineWindow, cursorHandler);
}

void mes::MaxwellEngine::enableKeyHandler()
{
    handleKeyConfig = true;
}


void mes::MaxwellEngine::stopRenderLoop()
{
    glfwSetWindowShouldClose(engineWindow, GLFW_TRUE);
}
