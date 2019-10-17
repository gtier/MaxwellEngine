//
//  TextureObject.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/19/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef TextureObject_hpp
#define TextureObject_hpp

#include <stdio.h>
#include "mes.h"

namespace mes {
    class TextureObject
    {
    private:
        std::string texturePath;
        unsigned int texture;
        
    public:
        TextureObject(const std::string& path);
        
        TextureObject(const TextureObject& textureObject);
        
        unsigned int getTexture();
    };
}

#endif /* TextureObject_hpp */
