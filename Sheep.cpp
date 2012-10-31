//
//  Sheep.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Sheep.h"

Sheep::Sheep() {
    model=new ObjModel("sheep", "sheep");
    position=glm::vec3(0,0,-4);
}

ObjModel * Sheep::getModel() {
    return model;
}

Sheep::~Sheep() {
    delete model;
}

glm::mat4 Sheep::getPositionMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Sheep::getModelMatrix() {
    return getPositionMatrix();
}