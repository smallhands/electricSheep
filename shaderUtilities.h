#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#define _GNU_SOURCE

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Glut/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#ifndef shader_Utilities_h
#define shader_Utilities_h

char* readFile(const char* filename);
GLuint createShader(const char *filename, GLenum shaderType);
void printCompilationLog(GLuint object);
bool bindShaderAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName);
bool bindShaderUniformAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName);

#endif
