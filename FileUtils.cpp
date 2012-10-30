//
//  FileUtils.cpp
//  electricSheep
//
//  Created by Ali Helmy on 30/10/2012.
//  Copyright (c) 2012 wackyCube. All rights reserved.
//

#include "FileUtils.h"

char* readFile(const char* filename) {
    FILE *inputFile=fopen(filename, "rb");
    if(inputFile==NULL) {
        return NULL;
    }
    
    int resourceBufferSize=BUFSIZ;
    char *resource=(char *)malloc(resourceBufferSize);
    int resourceTotalRead=0;
    
    while (!feof(inputFile) && !ferror(inputFile)) {
        if (resourceTotalRead+BUFSIZ > resourceBufferSize) {
            if(resourceBufferSize > 10*1024*1024) {
                break;
            }
            resourceBufferSize*=2;
            resource=(char *)realloc(resource, resourceBufferSize);
        }
        char *position=resource+resourceTotalRead;
        resourceTotalRead+=fread(position, 1, BUFSIZ, inputFile);
    }
    
    fclose(inputFile);
    resource=(char *)realloc(resource, resourceTotalRead+1);
    resource[resourceTotalRead]='\0';
    return resource;
}