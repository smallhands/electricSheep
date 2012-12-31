//
//  launcher.cpp
//  cubezOSX
//
//  Created by Ali Helmy on 06/11/2012.
//
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GLIncludes.h"
#include "electricsheep.h"

ElectricSheepEngine *_electricSheepEngine;

//windowSize
#define DEFAULT_WINDOW_WIDTH    1024
#define DEFAULT_WINDOW_HEIGHT   768

void freeResources() {
    delete _electricSheepEngine;
}

void render() {
    _electricSheepEngine->render();
    
    //blit drawn screen
    glutSwapBuffers();
}

void reshape(int newWindowWidth, int newWindowHeight)
{
    _electricSheepEngine->reshape(newWindowWidth, newWindowHeight);
}

void update()
{
    GLfloat timeElapsed = glutGet(GLUT_ELAPSED_TIME);
    
    _electricSheepEngine->update(timeElapsed);
    
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    glutCreateWindow("Electric Sheep");
    
#ifdef _WIN32
    /* Extension wrangler initialising */
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return EXIT_FAILURE;
    }
#endif
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(render);
    glutIdleFunc(idle);
    
    _electricSheepEngine=new ElectricSheepEngine(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    _electricSheepEngine->initWorld();
    
    glutMainLoop();
    
    freeResources();
    return 0;
}
