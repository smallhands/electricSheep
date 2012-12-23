//
//  GameObject.cpp
//  electricSheep
//
//  Created by Ali Helmy on 23/12/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "GameObject.h"
#include <math.h>

int randomNumber(int min, int max) {
    static bool randomSeeded=false;
    if(!randomSeeded) {
        srand(time(0));
        randomSeeded=true;
    }
    return (rand()%(max-min))+min;
}

GameObject::GameObject() {
    position = glm::vec3(0, 0, 0);
    heading = glm::vec3(1, 0, 0);
    heading = glm::normalize(heading);
}

Model * GameObject::getModel() {
    return model;
}

glm::mat4 GameObject::getPositionMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 GameObject::getRotationMatrix() {
    static glm::vec3 originalHeading=glm::vec3(1, 0, 0);
    GLfloat dot=glm::dot(heading, originalHeading);
    GLfloat angle=acos(dot) * 180 / M_2_PI;
    return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0,0,1));
}

glm::mat4 GameObject::getModelMatrix() {
    return getPositionMatrix() * getRotationMatrix();
}

GameObject::~GameObject() {
    
}