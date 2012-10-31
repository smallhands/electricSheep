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
#include "GLIncludes.h"
#include "shaderUtilities.h"
#include "Sheep.h"
#include "Land.h"
#include <vector>

class ElectricSheepEngine {
    
public:
    ElectricSheepEngine();
    ~ElectricSheepEngine();
    bool initShaders(const char *vertexShaderSource, const char *fragmentShaderSource);
    void initSheep();
    void update(GLfloat elapsedTime);
    void render();
    void reshape(int newWindowWidth, int newWindowHeight);

private:
    GLuint shaderProgram;
    GLint shaderAttribute_coord3D;
    GLint shaderAttribute_vertexColour;
    GLint shaderAttribute_TexCoordIn;
    GLint shaderAttribute_uniform_mvp;
    GLint shaderAttribute_uniform_Texture;
    
    std::vector<Sheep *> herd;
    Land *land;
    
    void freeResources();
    
    void renderObjectModel(ObjModel *model, glm::mat4 modelMatrix);
};

#endif
