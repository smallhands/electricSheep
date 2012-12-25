//
//  CubeModel.cpp
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "CubeModel.h"
#include "Path_C_Interface.h"
#include <vector>

using namespace std;

CubeModel::CubeModel() : Model() {
    vector<GLushort> faces;
    vector<modelData> modelDataMap;
    
    modelData data[] = {
        // front
        {{-1.0, -1.0,  1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}},
        {{ 1.0, -1.0,  1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        {{ 1.0,  1.0,  1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0,  1.0,  1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        // top
        {{-1.0,  1.0,  1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}},
        {{ 1.0,  1.0,  1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        {{ 1.0,  1.0, -1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0,  1.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        // back
        {{ 1.0, -1.0, -1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}},
        {{-1.0, -1.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0,  1.0, -1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{ 1.0,  1.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        // bottom
        {{-1.0, -1.0, -1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}},
        {{ 1.0, -1.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        {{ 1.0, -1.0,  1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0, -1.0,  1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        // left
        {{-1.0, -1.0, -1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}},
        {{-1.0, -1.0,  1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0,  1.0,  1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0,  1.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        // right
        {{ 1.0, -1.0,  1.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}},
        {{ 1.0, -1.0, -1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
        {{ 1.0,  1.0, -1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{ 1.0,  1.0,  1.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}},
    };
    
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
    
    //calculate models for vertices [FLAT SHADING]
    for (int faceIndex=0; faceIndex<12; faceIndex++) {
        GLushort vi0, vi1, vi2;
        vi0 = cubeFaces[(faceIndex*3)+0];
        vi1 = cubeFaces[(faceIndex*3)+1];
        vi2 = cubeFaces[(faceIndex*3)+2];
        
        glm::vec3 v0 = glm::vec3(data[vi0].coord3D[0], data[vi0].coord3D[1], data[vi0].coord3D[2]);
        glm::vec3 v1 = glm::vec3(data[vi1].coord3D[0], data[vi1].coord3D[1], data[vi1].coord3D[2]);
        glm::vec3 v2 = glm::vec3(data[vi2].coord3D[0], data[vi2].coord3D[1], data[vi2].coord3D[2]);
        
        glm::vec3 v01 = v1 - v0;
        glm::vec3 v12 = v2 - v1;
        
        glm::vec3 normal = glm::cross(v01, v12);
        normal = glm::normalize(normal);
        
        data[vi0].normal[0] = data[vi1].normal[0] = data[vi2].normal[0] = normal.x;
        data[vi0].normal[1] = data[vi1].normal[1] = data[vi2].normal[1] = normal.y;
        data[vi0].normal[2] = data[vi1].normal[2] = data[vi2].normal[2] = normal.z;
    }
    
    for (int vi=0; vi<24; vi++) {
        modelDataMap.push_back(data[vi]);
    }
    
    for (int fi=0; fi<36; fi++) {
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
}

CubeModel::~CubeModel() {
    
}
