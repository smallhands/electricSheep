//
//  electricObject.cpp
//  electricSheep
//
//  Created by Ali Helmy on 20/12/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "electricObject.h"

ElectricObject::ElectricObject() : position(0.0, 0.0, 0.0), model() {
    
}

ObjModel ElectricObject::getModel() {
    return this->model;
}

glm::mat4 ElectricObject::getModelMatrix() {
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, this->position);
    return modelMatrix;
}

void ElectricObject::setPosition(glm::vec3 aNewPosition) {
    this->position.x = aNewPosition.x;
    this->position.y = aNewPosition.y;
    this->position.z = aNewPosition.z;
}