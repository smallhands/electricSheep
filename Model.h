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

struct modelData {
    GLfloat coord3D[3];
    GLfloat color[3];
};

class Model {
protected:
    GLuint modelVerticesBufferObject;
    GLuint modelFacesBufferObject;

public:
    Model();
    virtual ~Model();
    GLuint getVerticesBufferObject();
    GLuint getFacesBufferObject();
};

#endif
