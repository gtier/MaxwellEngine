//
//  TextureObject.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/19/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include "TextureObject.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

mes::TextureObject::TextureObject(const std::string& path)
: texturePath(path)
{
    std::cout << "Building texture object" << std::endl;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    //Makes textures repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Makes textures scale with linear sample selection
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, channelNum;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * textureData = stbi_load(texturePath.c_str(), &width, &height, &channelNum, 0);
    
    if (textureData)
    {
        std::cout << "Texture load success: " + texturePath;
        //glTexImage2D arguments
        //Target texture, mipmap level, storage color format, width, height, legacy support, format of textureData, datatype of textureData source, source image.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        throw "Failed to load texture: " + texturePath;
    }
    
    stbi_image_free(textureData);
}

mes::TextureObject::TextureObject(const TextureObject& textureObject)
{
    std::cout << "Texture object copy constructor!" << std::endl;
    texturePath = textureObject.texturePath;
    texture = textureObject.texture;
}

unsigned int mes::TextureObject::getTexture()
{
    return texture;
}
