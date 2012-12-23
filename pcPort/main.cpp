#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../GLIncludes.h"

#define WINDOW_TITLE	"Electric Sheep"

int CurrentWidth = 800,
	CurrentHeight = 600,
	WindowHandle = 0;

void initialize(int, char*[]);
void createWindow(int, char*[]);
void resizeFunction(int, int);
void renderFunction(void);
void updateFunction(void);

int main(int argc, char* argv[]) {
	initialize(argc, argv);

	glutMainLoop();
	
	exit(EXIT_SUCCESS);
}

void initialize(int argc, char* argv[]) {
	glutInit(&argc, argv);

	createWindow(argc, argv);
	
	glutReshapeFunc(resizeFunction);
	glutDisplayFunc(renderFunction);
	glutIdleFunc(updateFunction);

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);
}

void createWindow(int argc, char* argv[]) {	
	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE);

	if(WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}
}

void updateFunction(void) {

}

void resizeFunction(int Width, int Height) {
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void renderFunction(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glutPostRedisplay();
}
