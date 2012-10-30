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
    GLfloat colour3D[3];
};

class ObjModel {
    GLuint modelVerticesBufferObject;
    GLuint modelFacesBufferObject;
    GLuint textureID;
    
public:
    ObjModel(const char *objFilePath);
    ~ObjModel();
    GLuint getVerticesBufferObject();
    GLuint getFacesBufferObject();
};

#endif /* defined(__electricSheep__ObjModel__) */
