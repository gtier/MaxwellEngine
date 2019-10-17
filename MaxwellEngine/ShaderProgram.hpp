//
//  ShaderProgram.hpp
//  GriffRoboVoxelTech
//
//  Created by student on 3/22/19.
//  Copyright © 2019 student. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include "mes.h"
#include "ShaderFile.hpp"

namespace mes {
    enum UniformType {
        U1I, U1F, U1D
    };
    
    class ShaderProgram {
    private:
        const char * vertexChar;
        const char * fragmentChar;
        unsigned int id;
        bool built = false;
        
    public:
        ShaderProgram(mes::ShaderFile& vertexShaderFile, mes::ShaderFile& fragmentShaderFile)
        : vertexChar(vertexShaderFile.read()), fragmentChar(fragmentShaderFile.read()), id(0)
        {
        }
        
        void use() {
            glUseProgram(id);
        }
        
        unsigned int getId()
        {
            return id;
        }
        
        //Pass in args and specific glUniform set function from OpenGL (e.g. glUniform1i or glUniform2f)
        template<class F, typename... Args>
        void setUniform(std::string name, F glFunc, Args... args) {
            if (!built)
            {
                throw "Shader must be built!";
            }
            try {
                glFunc(glGetUniformLocation(id, name.c_str()), args...);
                
            } catch (std::exception&  e) {
                throw e;
            }
            
        }
        
        unsigned int build()
        {
            if (built) {
                throw "Shader has already been built!";
            } else {
                built = true;
            }
            
            unsigned int vertShader = 0;
            vertShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertShader, 1, &vertexChar, NULL);
            glCompileShader(vertShader);
            
            int compileSuccess;
            char compileInfoLog[512];
            glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compileSuccess);
            
            if (!compileSuccess)
            {
                glGetShaderInfoLog(vertShader, 512, NULL, compileInfoLog);
                std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << compileInfoLog << std::endl;
                throw "ERROR::SHADER::VERTEX::COMPILATION_FAILED";
            }
            
            unsigned int fragmentShader = 0;
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentChar, NULL);
            glCompileShader(fragmentShader);
            
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);
            
            if (!compileSuccess)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, compileInfoLog);
                std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << compileInfoLog << std::endl;
                throw "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED";
            }
            
            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            
            int linkSuccess;
            char linkInfoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
            
            if (!linkSuccess)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, linkInfoLog);
                std::cerr <<  "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << linkInfoLog << std::endl;
                throw  "ERROR::SHADER::PROGRAM::LINK_FAILED";
            }
            
            glDeleteShader(vertShader);
            glDeleteShader(fragmentShader);
            
            id = shaderProgram;
            return shaderProgram;
        }
    };
}



#endif /* ShaderProgram_hpp */
