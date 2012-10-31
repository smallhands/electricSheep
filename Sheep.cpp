//
//  Sheep.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Sheep.h"
#include <sstream>

Sheep::Sheep() {
    state=SHEEP_STATE_IDLE;
    animationIndex=0;
    position=glm::vec3(0,0,0);
    
    loadStateModels();
}

ObjModel * Sheep::getModel() {
    return (stateModels[state])[animationIndex];
}

void Sheep::loadStateModels() {
    std::vector<ObjModel *> idleAnimationModels;
    std::vector<ObjModel *> grazeAnimationModels;
    std::vector<ObjModel *> walkAnimationModels;
    
    idleAnimationModels.push_back(new ObjModel("sheep", "sheep"));
    
    for (int i=0; i<4; i++) {
        std::ostringstream grazeAnimationName;
        grazeAnimationName << "sheep_anim_graze" << i;
        std::string grazeAnimationFullName(grazeAnimationName.str());
        grazeAnimationModels.push_back(new ObjModel(grazeAnimationFullName.c_str(), "sheep"));
        
        std::ostringstream walkAnimationName;
        walkAnimationName << "sheep_anim_walk" << i;
        std::string walkAnimationFullName(walkAnimationName.str());
        walkAnimationModels.push_back(new ObjModel(walkAnimationFullName.c_str(), "sheep"));
    }
    
    stateModels[SHEEP_STATE_IDLE]=idleAnimationModels;
    stateModels[SHEEP_STATE_GRAZING]=grazeAnimationModels;
    stateModels[SHEEP_STATE_WALKING]=walkAnimationModels;
}

Sheep::~Sheep() {
    stateModels.clear();
}

glm::mat4 Sheep::getPositionMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Sheep::getModelMatrix() {
    return getPositionMatrix();
}

#define animationThreshold 400

void Sheep::update(GLfloat elapsedTime) {
    if (elapsedTime>animationThreshold) {
        animationIndex+=1;
        if (animationIndex>=stateModels[state].size()) {
            animationIndex=0;
        }
    }
}