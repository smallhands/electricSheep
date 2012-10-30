//
//  ObjModel.h
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__ObjModel__
#define __electricSheep__ObjModel__

#include <iostream>
#include "GLIncludes.h"

class ObjModel {
    GLfloat *vertices;
    GLfloat *faces;
    
public:
    ObjModel(const char *objFilePath);
    ~ObjModel();
};

#endif /* defined(__electricSheep__ObjModel__) */
