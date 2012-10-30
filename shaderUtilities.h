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
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#ifndef shader_Utilities_h
#define shader_Utilities_h

GLuint createShader(const char *shaderSourcePath, GLenum shaderType);
void printCompilationLog(GLuint object);
bool bindShaderAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName);
bool bindShaderUniformAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName);

#endif
