//
//  electricsheep.h
//  electricSheep
//
//  Created by Ali Helmy on 23/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#ifndef electricSheep_electricsheep_h
#define electricSheep_electricsheep_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderUtilities.h"

class ElectricSheepEngine {
    GLuint shaderProgram;
    GLint shaderAttribute_coord3D;
    GLint shaderAttribute_vertexColour;
    GLint shaderAttribute_uniform_mvp;
    GLint shaderAttribute_uniform_animation;
    //model vertices
    GLuint modelDataVBO;
    GLuint modelElements;
    
public:
    static ElectricSheepEngine getInstance();
    ~ElectricSheepEngine();
    bool initShaders(const char *vertexShaderSource, const char *fragmentShaderSource);
    void update();
    void render();
    void reshape(int newWindowWidth, int newWindowHeight);

private:
    void freeResources();
    ElectricSheepEngine();
};

#endif
