//
//  VoxwellEngine.hpp
//  GriffRoboVoxelTech
//
//  Created by student on 4/23/19.
//  Copyright © 2019 student. All rights reserved.
//

#ifndef VoxwellEngine_hpp
#define VoxwellEngine_hpp

#include <stdio.h>
#include "mes.h"
#include "MaxwellEngine.hpp"
#include "RenderObject.hpp"
#include "ShaderFile.hpp"
#include <thread>
#include <queue>

namespace ves {
    class VoxwellEngine
    {
    private:
        mes::MaxwellEngine engine;
    public:
        VoxwellEngine(int width, int height, mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader)
        : engine(width, height, vertShader, fragmentShader)
        {
        }
        
        void start();
        
        void load();
        
        void render();
        
    private:
        void init();
    };
}

#endif /* VoxwellEngine_hpp */
