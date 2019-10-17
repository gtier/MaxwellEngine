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
#include <iostream>
#include "mes.h"


class mes::CameraObject
{
public:
    typedef void (*cursorHandler_t)(GLFWwindow* window, double x, double y);
private:
    glm::vec3 position, front, target, universalUp, right, up;
    float pitch, yaw, prevX, prevY, sensitivity, speed;
    glm::mat4 viewMatrix, projectionMatrix;
public:
    CameraObject(int width, int height)
    : viewMatrix(1.0f), position(0.0f, 0.0f, 2.0f), target(0.0f, 0.0f, 0.0f), universalUp(0.0f, 1.0f, 0.0f), prevX(0.0f), prevY(0.0f), sensitivity(0.025f), speed(2.0f)
    {
        projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 1000.0f);
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = universalUp;
        viewMatrix = glm::lookAt(position, position + front, up);
    }
    
    const glm::mat4& getViewMatrix() const
    {
        return viewMatrix;
    }
    
    const glm::mat4& getProjectionMatrix() const
    {
        return projectionMatrix;
    }
    
    void updateViewMatrix()
    {
        viewMatrix = glm::lookAt(position, position + front, universalUp);
        right = glm::normalize(glm::cross(front, universalUp));
        up = glm::normalize(glm::cross(right, front));
    }
    
    void cursorHandler(GLFWwindow* window, double x, double y)
    {
        float xOff = x - prevX;
        float yOff = y - prevY;
        prevX = x;
        prevY = y;
        
        xOff *= sensitivity;
        yOff *= sensitivity;
        
        yaw += xOff;
        pitch -= yOff;
        
        if (pitch > 89.9f) {
            pitch = 89.9f;
        } else if (pitch < -89.9f) {
            pitch = -89.9f;
        }
        
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        front = glm::normalize(front);
        updateViewMatrix();
    }
    
    void keyHandler(GLFWwindow* window, float deltaFrameTime)
    {
        float displacement = speed * deltaFrameTime;
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position += displacement * front;
        } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position -= displacement * front;
        }
        
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position += displacement * glm::cross(front, up);
        } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position -= displacement * glm::cross(front, up);
        }
        
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            position += displacement * universalUp;
        }else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            position -= displacement * universalUp;
        }
        
        updateViewMatrix();
    }
    
    void setSpeed(float magnitude)
    {
        speed = magnitude;
    }
    
    void setSensitivity(float magnitude)
    {
        sensitivity = magnitude;
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
