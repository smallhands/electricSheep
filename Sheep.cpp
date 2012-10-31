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
    state=SHEEP_STATE_GRAZING;
    animationIndex=0;
    position=glm::vec3(randomNumber(-5, 5),randomNumber(-5, 5),0);
    heading=glm::vec2(randomNumber(-10, 10),randomNumber(-10, 10));
    heading=glm::normalize(heading);
    
    loadStateModels();
    
    stateTime[SHEEP_STATE_IDLE]=0;
    stateTime[SHEEP_STATE_GRAZING]=0;
    stateTime[SHEEP_STATE_WALKING]=0;
    
    currentAnimationTime=0;
    
    lastUpdateTime=0;
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

glm::mat4 Sheep::getRotationMatrix() {
    static glm::vec2 originalHeading=glm::vec2(1,0);
    GLfloat dot=glm::dot(heading, originalHeading);
    GLfloat angle=acos(dot) * 180 / M_2_PI;
    return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0,0,1));
}

glm::mat4 Sheep::getModelMatrix() {
    return getPositionMatrix() * getRotationMatrix();
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
    
    if (state==SHEEP_STATE_WALKING) {
        heading.x+=((float)randomNumber(-1, 1))/20.0;
        heading.y+=((float)randomNumber(-1, 1))/20.0;
        heading=glm::normalize(heading);
    }
    
    animationIndex=0;
    stateTime[state]=0;
}

#define animationThreshold  20
#define stateThreshold      400

void Sheep::update(GLfloat elapsedTime) {
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
    if ((state!=SHEEP_STATE_WALKING && stateTime[state]>stateThreshold) || stateTime[state]>stateThreshold/10) {
        switchState();
    }
    
    if (state==SHEEP_STATE_WALKING) {
        position.x+=0.005*heading.x;
        position.y+=0.005*heading.y;
    }
    
    lastUpdateTime=elapsedTime;
}