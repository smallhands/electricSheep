#include "shaderUtilities.h"

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

void printCompilationLog(GLuint objectID) {
    GLint shaderCompilationInfoLogLength = 0;	
    glGetShaderiv(objectID, GL_INFO_LOG_LENGTH , &shaderCompilationInfoLogLength);
    GLchar* compilerLog = new GLchar[shaderCompilationInfoLogLength];
    GLsizei slen = 0;
    glGetShaderInfoLog(objectID, shaderCompilationInfoLogLength, &slen, compilerLog);
    fprintf(stderr, "compiler_log: %s", compilerLog);
    delete compilerLog;
}

bool bindShaderAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName) {
    *shaderAttribute=glGetAttribLocation(shaderProgram, shaderAttributeName);
    return *shaderAttribute!=-1;
}

bool bindShaderUniformAttribute(GLint *shaderAttribute, GLuint shaderProgram, const char *shaderAttributeName){
    *shaderAttribute=glGetUniformLocation(shaderProgram, shaderAttributeName);
    return *shaderAttribute!=-1;
}

GLuint createShader(const char *filename, GLenum shaderType) {
    const char *shaderSource=readFile(filename);
    if(shaderSource==NULL) {
        fprintf(stderr, "ERROR: Could not open shader source file: %s", filename);
        return 0;
    }
    
    GLuint shaderID=glCreateShader(shaderType);
    const GLchar *shaderSources[]={
        // Define GLSL version
#if defined(EMSCRIPTEN) || defined (GL_ES_VERSION_2_0)
        "#version 100\n"
#else
        "#version 120\n"
#endif
        ,
        // GLES2 precision specifiers
#if defined(EMSCRIPTEN) || defined (GL_ES_VERSION_2_0)
        // Define default float precision for fragment shaders:
        (shaderType == GL_FRAGMENT_SHADER) ?
        "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
        "precision highp float;           \n"
        "#else                            \n"
        "precision mediump float;         \n"
        "#endif                           \n"
        : ""
        // Note: OpenGL ES automatically defines this:
        // #define GL_ES
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
