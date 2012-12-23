//
//  Model.cpp
//  electricSheep
//
//  Created by Ali Helmy on 23/12/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Model.h"

Model::Model() {
    
}

Model::~Model() {
    glDeleteBuffers(1, &modelVerticesBufferObject);
    glDeleteBuffers(1, &modelFacesBufferObject);
}

GLuint Model::getVerticesBufferObject() {
    return modelVerticesBufferObject;
}

GLuint Model::getFacesBufferObject() {
    return modelFacesBufferObject;
}