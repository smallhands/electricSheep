// third-party libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GLIncludes.h"
#include "electricsheep.h"

ElectricSheepEngine *_electricSheepEngine;

//defaults
#define DEFAULT_WINDOW_WIDTH    1024
#define DEFAULT_WINDOW_HEIGHT   768
#define OPENGL_VERSION_MAJOR	2
#define	OPENGL_VERSION_MINOR	1

void freeResources() {
    delete _electricSheepEngine;
}

void init() {
	_electricSheepEngine = new ElectricSheepEngine(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    _electricSheepEngine->initWorld();
}

void render() {
    _electricSheepEngine->render();
    
	glfwSwapBuffers();
}

void reshape(int newWindowWidth, int newWindowHeight)
{
    _electricSheepEngine->reshape(newWindowWidth, newWindowHeight);
}

void update()
{
	GLfloat timeElapsed = 0;
#pragma message ("TODO: [GLFW] Find way to get elapsed time in GLFW")
    //timeElapsed = glutGet(GLUT_ELAPSED_TIME);
    
    _electricSheepEngine->update(timeElapsed);
}

// the program starts here
void AppMain() {
    // initialise GLFW
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if(!glfwOpenWindow((int)DEFAULT_WINDOW_WIDTH, (int)DEFAULT_WINDOW_HEIGHT, 8, 8, 8, 8, 0, 0, GLFW_WINDOW)) {
		auto errorString = std::string("glfwOpenWindow failed. Can your hardware handle OpenGL ");
		errorString += OPENGL_VERSION_MAJOR + "." + OPENGL_VERSION_MINOR;
		throw std::runtime_error(errorString);
	}
    
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // make sure OpenGL version API is available
	if(!GLEW_VERSION_2_1) {
		auto errorString = std::string("OpenGL ");
		errorString += OPENGL_VERSION_MAJOR + "." + OPENGL_VERSION_MINOR;
		errorString += " API is not available.";
		throw std::runtime_error(errorString);
	}

	init();

    // run while the window is open
    while(glfwGetWindowParam(GLFW_OPENED)){
		update();
        render();
    }

    // clean up and exit
    glfwTerminate();
}


int main(int argc, char *argv[]) {
    try {
        AppMain();
    } catch (const std::exception& e){
        std::cerr << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}