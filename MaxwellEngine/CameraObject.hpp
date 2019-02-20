//
//  CameraObject.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/19/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef CameraObject_hpp
#define CameraObject_hpp

#include <stdio.h>
#include "mes.h"


class mes::CameraObject
{
private:
    glm::mat4 viewMatrix, projectionMatrix;
public:
    CameraObject(int width, int height)
    : viewMatrix(1.0f)
    {
        projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 1000.0f);
    }
    
    const glm::mat4& getViewMatrix() const
    {
        return viewMatrix;
    }
    
    const glm::mat4& getProjectionMatrix() const
    {
        return projectionMatrix;
    }
    
    void setViewMatrix(const glm::mat4& matrix)
    {
        viewMatrix = matrix;
    }
    
    void setProjectionMatrix(const glm::mat4& matrix)
    {
        projectionMatrix = matrix;
    }
    
    glm::mat4 getMultiplied()
    {
        return projectionMatrix * viewMatrix;
    }
};

#endif /* CameraObject_hpp */
