//
//  VoxwellEngine.cpp
//  GriffRoboVoxelTech
//
//  Created by student on 4/23/19.
//  Copyright © 2019 student. All rights reserved.
//

#include "VoxwellEngine.hpp"

void ves::VoxwellEngine::init()
{
    engine.getMainCamera().setViewMatrix(glm::translate(engine.getMainCamera().getViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
    
    engine.getMainCamera().setSpeed(10.0f);
    
    engine.getMainCamera().setSensitivity(0.25f);
    
    engine.enableCursorHanler();
    
    engine.mountStaticCamera();
}


void ves::VoxwellEngine::start()
{
    //Set up VoxwellEngine to start on another thread
    //Make a command queue
    
    engine.startRenderLoop();
}
