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
    ElectricSheepEngine(float width, float height);
    ~ElectricSheepEngine();
    void initWorld();
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
    
    //view matrix using look at
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUp;
    glm::mat4 view;
    
    //projection matrix
    GLfloat lensAngle;
    GLfloat aspectRatio;
    GLfloat nearClippingPlane;
    GLfloat farClippingPlane;
    glm::mat4 projection;
    
    std::vector<Sheep *> herd;
    Land *land;
    
    bool initShaders(const char *vertexShaderSource, const char *fragmentShaderSource);
    void initCamera();
    void initProjection();
    
    void freeResources();
    
    void renderObjectModel(ObjModel *model, glm::mat4 modelMatrix);
};

#endif
