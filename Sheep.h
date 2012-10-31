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
#include <vector>
#include <map>

typedef enum {
    SHEEP_STATE_IDLE,
    SHEEP_STATE_WALKING,
    SHEEP_STATE_GRAZING
}SheepState;

class Sheep {
    glm::vec3 position;
    SheepState state;
    GLubyte animationIndex;
    std::map<SheepState, std::vector<ObjModel *> > stateModels;
    
    glm::mat4 getPositionMatrix();
    void loadStateModels();
public:
    Sheep();
    ~Sheep();
    ObjModel * getModel();
    glm::mat4 getModelMatrix();
    void update(GLfloat elapsedTime);
};

#endif /* defined(__electricSheep__Sheep__) */
