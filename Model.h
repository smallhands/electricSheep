//
//  Model.h
//  electricSheep
//
//  Created by Ali Helmy on 23/12/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef electricSheep_Model_h
#define electricSheep_Model_h

#include "GLIncludes.h"
#include "TexturesMap_C_Interface.h"

struct modelData {
    GLfloat coord3D[3];
    GLfloat texCoords[2];
};

class Model {
protected:
    GLuint modelVerticesBufferObject;
    GLuint modelFacesBufferObject;
    GLuint textureID;

public:
    Model();
    virtual ~Model();
    GLuint getVerticesBufferObject();
    GLuint getFacesBufferObject();
    GLuint getTextureID();
};

#endif
