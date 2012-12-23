//
//  GameObject.h
//  electricSheep
//
//  Created by Ali Helmy on 23/12/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__GameObject__
#define __electricSheep__GameObject__

#include <iostream>
#include "Model.h"

class GameObject {
protected:
    glm::vec3 position;
    glm::vec3 heading;
    
    Model *model;
    
    glm::mat4 getPositionMatrix();
    glm::mat4 getRotationMatrix();
    
public:
    GameObject();
    virtual ~GameObject();
    Model * getModel();
    glm::mat4 getModelMatrix();
    virtual void update(GLfloat elapsedTime) = 0;
};


#endif /* defined(__electricSheep__GameObject__) */
