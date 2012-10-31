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

class Sheep {
    ObjModel *model;
    
public:
    Sheep();
    ~Sheep();
    ObjModel * getModel();
};

#endif /* defined(__electricSheep__Sheep__) */
