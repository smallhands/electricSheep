#include "shaderUtilities.h"
#include "FileUtils.h"

void printCompilationLog(GLuint objectID) {
    GLint shaderCompilationInfoLogLength = 0;	
    glGetShaderiv(objectID, GL_INFO_LOG_LENGTH , &shaderCompilationInfoLogLength);
    GLchar* compilerLog = new GLchar[shaderCompilationInfoLogLength];
    GLsizei slen = 0;
    glGetShaderInfoLog(objectID, shaderCompilationInfoLogLength, &slen, compilerLog);
    fprintf(stderr, "compiler_log: %s", compilerLog);
    delete compilerLog;
}

bool bindShaderAttribute(GLint &shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName) {
    shaderAttribute=glGetAttribLocation(shaderProgram, shaderAttributeName);
    return shaderAttribute!=-1;
}

bool bindShaderUniformAttribute(GLint &shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName){
    shaderAttribute=glGetUniformLocation(shaderProgram, shaderAttributeName);
    return shaderAttribute!=-1;
}

GLuint createShader(const char *shaderSourcePath, GLenum shaderType) {
    const char *shaderSource=readFile(shaderSourcePath);
    GLuint shaderID=glCreateShader(shaderType);
    const GLchar *shaderSources[]={
        // Define GLSL version
#ifdef GL_ES_VERSION_2_0
        "#version 100\n"
#else
        "#version 120\n"
#endif
        ,
        // GLES2 precision specifiers
#ifdef GL_ES_VERSION_2_0
        // Define default float precision for fragment shaders:
        (shaderType == GL_FRAGMENT_SHADER) ?
        "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
        "precision highp float;           \n"
        "#else                            \n"
        "precision mediump float;         \n"
        "#endif                           \n"
        : ""
#else
        // Ignore GLES 2 precision specifiers:
        "#define lowp   \n"
        "#define mediump\n"
        "#define highp  \n"
#endif
        ,
        shaderSource
    };
    glShaderSource(shaderID, 3, shaderSources, NULL);
    free((void *)shaderSource);
    glCompileShader(shaderID);
    GLint compilationSuccess=GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationSuccess);
    if (compilationSuccess==GL_FALSE) {
        fprintf(stderr, "Shader Compilation Failure\n");
        printCompilationLog(shaderID);
        glDeleteShader(shaderID);
        return 0;
    }
    
    return shaderID;
}
