//
//  ObjModel.cpp
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "ObjModel.h"

ObjModel::ObjModel(const char *objFilePath) {
#pragma message("TODO: read in vertices & texture coords")
    struct modelData cube[] = {
        //front face
        {{-1.0, -1.0, 1.0}, {0.0, 0.0, 1.0}},
        {{ 1.0, -1.0, 1.0}, {0.0, 1.0, 1.0}},
        {{ 1.0,  1.0, 1.0}, {0.0, 0.0, 1.0}},
        {{-1.0,  1.0, 1.0}, {0.0, 1.0, 1.0}},
        //back face
        {{-1.0, -1.0, -1.0}, {0.0, 0.0, 1.0}},
        {{ 1.0, -1.0, -1.0}, {0.0, 1.0, 1.0}},
        {{ 1.0,  1.0, -1.0}, {0.0, 0.0, 1.0}},
        {{-1.0,  1.0, -1.0}, {0.0, 1.0, 1.0}}
    };
    glGenBuffers(1, &modelVerticesBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, modelVerticesBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
#pragma message("TODO: read in faces")
    GLushort cubeElements[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 0, 3,
        3, 7, 4,
        // left
        4, 5, 1,
        1, 0, 4,
        // right
        3, 2, 6,
        6, 7, 3,
    };
    glGenBuffers(1, &modelFacesBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelFacesBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeElements), cubeElements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //loadup textures
    textureID=textureForName("Brick_4");
}

GLuint ObjModel::getVerticesBufferObject() {
    return modelVerticesBufferObject;
}

GLuint ObjModel::getFacesBufferObject() {
    return modelFacesBufferObject;
}

ObjModel::~ObjModel() {
    glDeleteBuffers(1, &modelVerticesBufferObject);
    glDeleteBuffers(1, &modelFacesBufferObject);
}
