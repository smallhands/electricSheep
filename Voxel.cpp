//
//  Voxel.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Voxel.h"
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

Voxel::Voxel() {
    position=glm::vec3(0, 0, 0);
    heading=glm::vec2(randomNumber(-10, 10), randomNumber(-10, 10));
    heading=glm::normalize(heading);
    
    loadStateModels();
}

Model * Voxel::getModel() {
    return (stateModels[SHEEP_STATE_IDLE])[0];
}

void Voxel::loadStateModels(){
    std::vector<CubeModel *> idleAnimationModels;
    std::vector<CubeModel *> grazeAnimationModels;
    std::vector<CubeModel *> walkAnimationModels;
    
    idleAnimationModels.push_back(new CubeModel());
    
    stateModels[SHEEP_STATE_IDLE]=idleAnimationModels;
}

Voxel::~Voxel(){
    stateModels.clear();
}

glm::mat4 Voxel::getPositionMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Voxel::getRotationMatrix() {
    static glm::vec2 originalHeading=glm::vec2(1,0);
    GLfloat dot=glm::dot(heading, originalHeading);
    GLfloat angle=acos(dot) * 180 / M_2_PI;
    return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0,0,1));
}

glm::mat4 Voxel::getModelMatrix() {
    return getPositionMatrix() * getRotationMatrix();
}

void Voxel::update(GLfloat elapsedTime) {
    
}