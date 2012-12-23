//
//  Voxel.cpp
//  electricSheep
//
//  Created by Ali Helmy on 31/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "Voxel.h"
#include <sstream>
#include <time.h>
#include <stdlib.h>

Voxel::Voxel() : GameObject() {
    model = new CubeModel();
}

Voxel::~Voxel(){
    
}

void Voxel::update(GLfloat elapsedTime) {
    
}