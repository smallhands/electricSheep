//
//  ObjModel.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__ObjModel__
#define __electricSheep__ObjModel__

#include <iostream>
#include "GLIncludes.h"
#include "TexturesMap_C_Interface.h"

struct modelData {
    GLfloat coord3D[3];
    GLfloat texCoords[2];
};

class ObjModel {
protected:
    GLuint modelVerticesBufferObject;
    GLuint modelFacesBufferObject;
    GLuint textureID;
    
public:
    ObjModel();
    ObjModel(const char *objFilePath, const char *textureName);
    ~ObjModel();
    GLuint getVerticesBufferObject();
    GLuint getFacesBufferObject();
    GLuint getTextureID();
};



#endif /* defined(__electricSheep__ObjModel__) */
