#include "electricSheep.h"

//windowSize
int windowWidth=1136;
int windowHeight=640;

ElectricSheepEngine::ElectricSheepEngine() {
}

ElectricSheepEngine::~ElectricSheepEngine() {
    freeResources();
}

bool ElectricSheepEngine::initShaders(const char *vertexShaderPath, const char *fragmentShaderPath) {
    //load shaders & compile
    GLint linkSuccess=GL_FALSE;
    
    //vertex shader
    GLuint vertexShaderId=createShader(vertexShaderPath, GL_VERTEX_SHADER);
    
    //fragment shader
    GLuint fragmentShaderId=createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    
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
    
    const char *texCoordInAttributeName="TexCoordIn";
    if(!bindShaderAttribute(&shaderAttribute_TexCoordIn, shaderProgram, texCoordInAttributeName)){
        fprintf(stderr, "Could not bind shader attribute %s\n", texCoordInAttributeName);
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
    
    const char *textureAttributeName="Texture";
    if(!bindShaderUniformAttribute(&shaderAttribute_uniform_Texture, shaderProgram, textureAttributeName)){
        fprintf(stderr, "Could not bind shader attribute %s\n", textureAttributeName);
        return false;
    }
    
    //if nothing fails till here, shader init is a success
    return true;
}

void ElectricSheepEngine::initSheep() {
    Sheep *sheep=new Sheep();
    herd.push_back(sheep);
}

void ElectricSheepEngine::freeResources() {
    glDeleteProgram(shaderProgram);
    herd.clear();
}

//view matrix using look at
glm::vec3 cameraPosition=glm::vec3(0,2,0);
glm::vec3 cameraTarget=glm::vec3(0,0,-4); //same as model position to look at model
glm::vec3 cameraUp=glm::vec3(1,1,0);
glm::mat4 view=glm::lookAt(cameraPosition, cameraTarget, cameraUp);

//projection matrix
GLfloat lensAngle=45.0f;
GLfloat aspectRatio=1.0*(windowWidth/windowHeight);
GLfloat nearClippingPlane=0.1f;
GLfloat farClippingPlane=10.0f;
glm::mat4 projection=glm::perspective(lensAngle, aspectRatio, nearClippingPlane, farClippingPlane);

void ElectricSheepEngine::render() {
    //clear screen
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    //use the shader
    glUseProgram(shaderProgram);
    
    //enable attributes in program
    glEnableVertexAttribArray(shaderAttribute_coord3D);
    glEnableVertexAttribArray(shaderAttribute_TexCoordIn);
    
    for (std::vector<Sheep *>::size_type i=0; i!=herd.size(); i++) {
        Sheep *sheep=herd[i];
        ObjModel *model=sheep->getModel();
        
        //model matrix using model position vector
        glm::mat4 mvp=projection*view*sheep->getModelMatrix();
        glUniformMatrix4fv(shaderAttribute_uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
        
        glBindBuffer(GL_ARRAY_BUFFER, model->getVerticesBufferObject());
        glVertexAttribPointer(shaderAttribute_coord3D, // attribute
                              3, // number of elements per vertex, here (x,y)
                              GL_FLOAT, // the type of each element
                              GL_FALSE, // take our values as-is
                              sizeof(struct modelData), // coord every (sizeof) elements
                              0 // offset of first element
                              );
        
        glVertexAttribPointer(shaderAttribute_TexCoordIn, // attribute
                              2, // number of elements per vertex, here (r,g,b)
                              GL_FLOAT, // the type of each element
                              GL_FALSE, // take our values as-is
                              sizeof(struct modelData), // // coord every (sizeof) elements
                              (GLvoid *)(offsetof(struct modelData, texCoords)) // skip coords & colour coords
                              );
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, model->getTextureID());
        glUniform1i(shaderAttribute_uniform_Texture, 0);
        
        //draw the cube by going through its elements array
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getFacesBufferObject());
        int bufferSize;
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
        glDrawElements(GL_TRIANGLES, bufferSize/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    }
    
    //close up the attribute in program, no more need
    glDisableVertexAttribArray(shaderAttribute_coord3D);
    glDisableVertexAttribArray(shaderAttribute_TexCoordIn);
}

void ElectricSheepEngine::reshape(int newWindowWidth, int newWindowHeight)
{
    windowWidth=newWindowWidth;
    windowHeight=newWindowHeight;
    glViewport(0, 0, windowWidth, windowHeight);
}

void ElectricSheepEngine::update(GLfloat elapsedTime)
{
#pragma message("TODO: update game state")
    //animation matrix
    float angle = elapsedTime / 1000.0 * 45; // 45° per second
    glm::vec3 axis(1.0, -1.0, 0.0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis);
    glUniformMatrix4fv(shaderAttribute_uniform_animation, 1, GL_FALSE, glm::value_ptr(anim));
}