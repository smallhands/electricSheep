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

int randomNumber(int min, int max) {
    static bool randomSeeded=false;
    if(!randomSeeded) {
        srand(time(0));
        randomSeeded=true;
    }
    return (rand()%(max-min))+min;
}

Sheep::Sheep() {
    state=SHEEP_STATE_GRAZING;
    animationIndex=0;
    position=glm::vec3(0,0,0);
    
    loadStateModels();
    
    stateTime[SHEEP_STATE_IDLE]=0;
    stateTime[SHEEP_STATE_GRAZING]=0;
    stateTime[SHEEP_STATE_WALKING]=0;
    
    currentAnimationTime=0;
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

void Sheep::switchState() {
    int random=randomNumber(0, 100);
    switch (state) {
        case SHEEP_STATE_IDLE:
            if (random>80) {
                state=SHEEP_STATE_WALKING;
            } else if(random>=45) {
                state=SHEEP_STATE_GRAZING;
            }
            break;
        case SHEEP_STATE_WALKING:
            if (random>80) {
                state=SHEEP_STATE_IDLE;
            } else if(random>=65) {
                state=SHEEP_STATE_GRAZING;
            }
            break;
        case SHEEP_STATE_GRAZING:
            if (random>80) {
                state=SHEEP_STATE_WALKING;
            } else if(random>=65) {
                state=SHEEP_STATE_IDLE;
            }
            break;
        default:
            break;
    }
    animationIndex=0;
    stateTime[state]=0;
}

#define animationThreshold  20
#define stateThreshold      100

void Sheep::update(GLfloat elapsedTime) {
    static GLfloat lastUpdateTime=0;
    GLfloat deltaTime=elapsedTime-lastUpdateTime;
    currentAnimationTime+=deltaTime;
    if (currentAnimationTime>animationThreshold) {
        animationIndex+=1;
        currentAnimationTime=0;
        if (animationIndex>=stateModels[state].size()) {
            animationIndex=0;
        }
    }
    
    stateTime[state]+=deltaTime;
    if (stateTime[state]>stateThreshold) {
        switchState();
    }
    
    lastUpdateTime=elapsedTime;
}