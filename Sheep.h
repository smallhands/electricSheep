//
//  Sheep.h
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__Sheep__
#define __electricSheep__Sheep__

#include "ObjModel.h"
#include "GLIncludes.h"

class Sheep {
    ObjModel *model;
    glm::vec3 position;
    glm::mat4 getPositionMatrix();
public:
    Sheep();
    ~Sheep();
    ObjModel * getModel();
    glm::mat4 getModelMatrix();
};

#endif /* defined(__electricSheep__Sheep__) */
