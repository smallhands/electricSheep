//
//  Land.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Land.h"

Land::Land() {
    struct modelData modelDataMap[] = {
        {{-10.0, -10.0, 0.0}, {0.0, 0.0}},
        {{ 10.0, -10.0, 0.0}, {0.0, 1.0}},
        {{ 10.0,  10.0, 0.0}, {1.0, 0.0}},
        {{-10.0,  10.0, 0.0}, {1.0, 1.0}},
    };
    
    glGenBuffers(1, &modelVerticesBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, modelVerticesBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelDataMap), modelDataMap, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLushort faces[] = {
        0, 1, 2,
        2, 3, 0,
    };
    glGenBuffers(1, &modelFacesBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelFacesBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //loadup textures
    textureID=textureForName("grass");
}