//
//  Sheep.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Sheep.h"
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int randomNumber(int min, int max) {
    static bool randomSeeded=false;
    if(!randomSeeded) {
        srand(time(0));
        randomSeeded=true;
    }
    return (rand()%(max-min))+min;
}

Sheep::Sheep() {
    position=glm::vec3(0, 0, 0);
    heading=glm::vec2(randomNumber(-10, 10), randomNumber(-10, 10));
    heading=glm::normalize(heading);
    
    loadStateModels();
}

CubeModel * Sheep::getModel() {
    return (stateModels[SHEEP_STATE_IDLE])[0];
}

void Sheep::loadStateModels(){
    std::vector<CubeModel *> idleAnimationModels;
    std::vector<CubeModel *> grazeAnimationModels;
    std::vector<CubeModel *> walkAnimationModels;
    
    idleAnimationModels.push_back(new CubeModel());
    
    stateModels[SHEEP_STATE_IDLE]=idleAnimationModels;
}

Sheep::~Sheep(){
    stateModels.clear();
}

glm::mat4 Sheep::getPositionMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Sheep::getRotationMatrix() {
    static glm::vec2 originalHeading=glm::vec2(1,0);
    GLfloat dot=glm::dot(heading, originalHeading);
    GLfloat angle=acos(dot) * 180 / M_2_PI;
    return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0,0,1));
}

glm::mat4 Sheep::getModelMatrix() {
    return getPositionMatrix() * getRotationMatrix();
}

void Sheep::update(GLfloat elapsedTime) {
    
}