#include "electricSheep.h"

//windowSize
int windowWidth=1136;
int windowHeight=640;

ElectricSheepEngine ElectricSheepEngine::getInstance() {
    static ElectricSheepEngine sharedInstance=ElectricSheepEngine();
    return sharedInstance;
}

ElectricSheepEngine::ElectricSheepEngine() {
    
}

ElectricSheepEngine::~ElectricSheepEngine() {
    this->freeResources();
}

bool ElectricSheepEngine::initShaders(const char *vertexShaderSource, const char *fragmentShaderSource) {
    //load shaders & compile
    GLint linkSuccess=GL_FALSE;
    
    //vertex shader
    GLuint vertexShaderId=createShader(vertexShaderSource, GL_VERTEX_SHADER);
    
    //fragment shader
    GLuint fragmentShaderId=createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    //program
    shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
    if(linkSuccess==GL_FALSE){
        fprintf(stderr, "Shader Linking Failure\n");
        return false;
    }
    
    //shader attributes
    const char *coord2DAttributeName="coord3D";
    if(!bindShaderAttribute(&shaderAttribute_coord3D, shaderProgram, coord2DAttributeName)){
        fprintf(stderr, "Could not bind shader attribute %s\n", coord2DAttributeName);
        return false;
    }
    
    const char *vertexColourAttributeName="vertexColour";
    if(!bindShaderAttribute(&shaderAttribute_vertexColour, shaderProgram, vertexColourAttributeName)){
        fprintf(stderr, "Could not bind shader attribute %s\n", vertexColourAttributeName);
        return false;
    }
    
    const char *mvpMatrixAttributeName="mvp";
    if(!bindShaderUniformAttribute(&shaderAttribute_uniform_mvp, shaderProgram, mvpMatrixAttributeName)){
        fprintf(stderr, "Could not bind shader attribute %s\n", mvpMatrixAttributeName);
        return false;
    }
    
    const char *animationMatrixAttributeName="animation";
    if(!bindShaderUniformAttribute(&shaderAttribute_uniform_animation, shaderProgram, animationMatrixAttributeName)){
        fprintf(stderr, "Could not bind shader attribute %s\n", animationMatrixAttributeName);
        return false;
    }
    
    //if nothing fails till here, shader init is a success
    return true;
}

void ElectricSheepEngine::freeResources() {
    glDeleteProgram(shaderProgram);
#pragma message("TODO: delete model data")
}

void ElectricSheepEngine::render() {
    //clear screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //use the shader
    glUseProgram(shaderProgram);
    
    //enable attributes in program
    glEnableVertexAttribArray(shaderAttribute_coord3D);
    glEnableVertexAttribArray(shaderAttribute_vertexColour);
    
#pragma message("TODO: draw calls for every model")
    
    //close up the attribute in program, no more need
    glDisableVertexAttribArray(shaderAttribute_coord3D);
    glDisableVertexAttribArray(shaderAttribute_vertexColour);
}

void ElectricSheepEngine::reshape(int newWindowWidth, int newWindowHeight)
{
    windowWidth=newWindowWidth;
    windowHeight=newWindowHeight;
    glViewport(0, 0, windowWidth, windowHeight);
}

void ElectricSheepEngine::update()
{
#pragma message("TODO: update game state")
}