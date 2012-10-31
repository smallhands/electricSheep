//
//  ObjModel.cpp
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "ObjModel.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str, const string& delimiter = " ") {
    vector<string> tokens;
    
    string::size_type lastPos = 0;
    string::size_type pos = str.find(delimiter, lastPos);
    
    while (string::npos != pos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = pos + delimiter.size();
        pos = str.find(delimiter, lastPos);
    }
    
    tokens.push_back(str.substr(lastPos, str.size() - lastPos));
    return tokens;
}

ObjModel::ObjModel(const char *objFilePath, const char *textureName) {
    ifstream in(objFilePath, ios::in);
    
    vector<glm::vec3> vertices;
    vector<glm::vec2> texCoords;
    vector<GLushort> faces;
    vector<modelData> modelDataMap;
    
    string line;
    while (getline(in, line)) {
        if (line.substr(0,2)=="v ") {
            istringstream s(line.substr(2));
            glm::vec3 newVertex;
            s >> newVertex.x >> newVertex.y >> newVertex.z;
            vertices.push_back(newVertex);
        } else if (line.substr(0,3)=="vt ") {
            istringstream s(line.substr(3));
            glm::vec2 newTexCoords;
            s >> newTexCoords.x >> newTexCoords.y;
            texCoords.push_back(newTexCoords);
        } else if (line.substr(0,2)=="f ") {
            istringstream s(line.substr(2));
            for (int i=0; i<3; i++) {
                string fv;
                s >> fv;
                vector<string> parts;
                parts=split(fv,"/");
                GLushort fvv=atoi(parts[0].c_str())-1;
                GLushort fvt=atoi(parts[1].c_str())-1;
                glm::vec3 vertex=vertices[fvv];
                glm::vec2 tex=texCoords[fvt];
                struct modelData data={{vertex.x, vertex.y, vertex.z}, {tex.x, tex.y}};
                modelDataMap.push_back(data);
                faces.push_back(faces.size());
            }
        }
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
    textureID=textureForName(textureName);
}

GLuint ObjModel::getTextureID() {
    return textureID;
}

GLuint ObjModel::getVerticesBufferObject() {
    return modelVerticesBufferObject;
}

GLuint ObjModel::getFacesBufferObject() {
    return modelFacesBufferObject;
}

ObjModel::~ObjModel() {
    glDeleteBuffers(1, &modelVerticesBufferObject);
    glDeleteBuffers(1, &modelFacesBufferObject);
}
