//
//  Voxel.h
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef __electricSheep__Voxel__
#define __electricSheep__Voxel__

#include "CubeModel.h"
#include "GameObject.h"
#include <vector>
#include <map>

class Voxel : public GameObject {
    
public:
    Voxel();
    ~Voxel();
    virtual void update(GLfloat elapsedTime);
};

#endif /* defined(__electricSheep__Voxel__) */
