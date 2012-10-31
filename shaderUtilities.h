#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include "GLIncludes.h"

#ifndef shader_Utilities_h
#define shader_Utilities_h

GLuint createShader(const char *shaderSourcePath, GLenum shaderType);
void printCompilationLog(GLuint object);
bool bindShaderAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName);
bool bindShaderUniformAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName);

#endif
