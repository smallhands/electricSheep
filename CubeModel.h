//
//  ObjModel.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__CubeModel__
#define __electricSheep__CubeModel__

#include <iostream>
#include "GLIncludes.h"
#include "TexturesMap_C_Interface.h"

struct modelData {
    GLfloat coord3D[3];
    GLfloat texCoords[2];
};

class CubeModel {
protected:
    GLuint modelVerticesBufferObject;
    GLuint modelFacesBufferObject;
    GLuint textureID;
    
public:
    CubeModel();
    ~CubeModel();
    GLuint getVerticesBufferObject();
    GLuint getFacesBufferObject();
    GLuint getTextureID();
};



#endif /* defined(__electricSheep__CubeModel__) */
