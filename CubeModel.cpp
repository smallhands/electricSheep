//
//  CubeModel.cpp
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "CubeModel.h"
#include "Path_C_Interface.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

CubeModel::CubeModel() : Model() {
    vector<GLushort> faces;
    vector<modelData> modelDataMap;
    
    GLfloat cubeVertices[] = {
        // front
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // top
        -1.0,  1.0,  1.0,
        1.0,  1.0,  1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
        // back
        1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
        1.0,  1.0, -1.0,
        // bottom
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,
        // left
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0,
        // right
        1.0, -1.0,  1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        1.0,  1.0,  1.0
    };
    
    GLfloat cubeTexCoords[] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
    
    
    for (int vi=0; vi<6*12; vi+=3) {
        glm::vec3 vertex = glm::vec3(cubeVertices[vi], cubeVertices[vi+1], cubeVertices[vi+2]);
        glm::vec2 tex = glm::vec2(cubeTexCoords[(vi%4)*2], cubeTexCoords[((vi%4)*2)+1]);
        struct modelData data = {{vertex.x, vertex.y, vertex.z}, {tex.x, tex.y}};
        modelDataMap.push_back(data);
    }
    
    GLushort cubeFaces[] = {
        // front
        0,  1,  2,
        2,  3,  0,
        // top
        4,  5,  6,
        6,  7,  4,
        // back
        8,  9, 10,
        10, 11,  8,
        // bottom
        12, 13, 14,
        14, 15, 12,
        // left
        16, 17, 18,
        18, 19, 16,
        // right
        20, 21, 22,
        22, 23, 20,
    };
    
    for (int fi=0; fi<6*6; fi++) {
        faces.push_back(cubeFaces[fi]);
    }
    
    glGenBuffers(1, &modelVerticesBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, modelVerticesBufferObject);
    glBufferData(GL_ARRAY_BUFFER, modelDataMap.size()*sizeof(modelData), &(modelDataMap[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &modelFacesBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelFacesBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size()*sizeof(GLushort), &(faces[0]), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    //loadup textures
    textureID=textureForName("grass");
}

CubeModel::~CubeModel() {
    
}
