//
//  Sheep.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Sheep.h"

Sheep::Sheep() {
    model=new ObjModel("sheep", "sheep");
}

ObjModel * Sheep::getModel() {
    return model;
}

Sheep::~Sheep() {
    delete model;
}