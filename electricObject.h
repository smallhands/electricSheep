//
//  electricObject.h
//  electricSheep
//
//  Created by Ali Helmy on 20/12/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__electricObject__
#define __electricSheep__electricObject__

#include "GLIncludes.h"
#include "ObjModel.h"

class ElectricObject {
    glm::vec3 position;
    ObjModel model;
    
protected:
    virtual void loadModel() = 0;
    
public:
    ElectricObject();
    ~ElectricObject();
    
    ObjModel getModel();
    virtual glm::mat4 getModelMatrix();
    void setPosition(glm::vec3 aNewPosition);
    
    virtual void update(GLfloat elapsetTimeSinceLastUpdate) = 0;
};

#endif /* defined(__electricSheep__electricObject__) */
