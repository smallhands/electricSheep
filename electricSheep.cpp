#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shaderUtilities.h"

//windowSize
int windowWidth=640;
int windowHeight=480;

GLuint shaderProgram;
GLint shaderAttribute_coord3D;
GLint shaderAttribute_vertexColour;
GLint shaderAttribute_uniform_mvp;
GLint shaderAttribute_uniform_animation;
//model vertices
GLuint modelDataVBO;
GLuint modelElements;

bool initShaders() {
    //load shaders & compile
    GLint linkSuccess=GL_FALSE;
    
    //vertex shader
    GLuint vertexShaderId=createShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    
    //fragment shader
    GLuint fragmentShaderId=createShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    
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

struct modelData {
    GLfloat coord3D[3];
    GLfloat colour3D[3];
};

void initModels() {
    struct modelData cube[] = {
        //front face
        {{-1.0, -1.0,  1.0}, {0.0, 0.0, 1.0}},
        {{ 1.0, -1.0,  1.0}, {0.0, 1.0, 1.0}},
        {{ 1.0,  1.0,  1.0}, {0.0, 0.0, 1.0}},
        {{-1.0,  1.0,  1.0}, {0.0, 1.0, 1.0}},
        //back face
        {{-1.0, -1.0, -1.0}, {0.0, 0.0, 1.0}},
        {{ 1.0, -1.0, -1.0}, {0.0, 1.0, 1.0}},
        {{ 1.0,  1.0, -1.0}, {0.0, 0.0, 1.0}},
        {{-1.0,  1.0, -1.0}, {0.0, 1.0, 1.0}}
    };
    glGenBuffers(1, &modelDataVBO);
    glBindBuffer(GL_ARRAY_BUFFER, modelDataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLushort cubeElements[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 0, 3,
        3, 7, 4,
        // left
        4, 5, 1,
        1, 0, 4,
        // right
        3, 2, 6,
        6, 7, 3,
    };
    glGenBuffers(1, &modelElements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelElements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeElements), cubeElements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool initResources() {
    initModels();
    return initShaders();
}

void freeResources() {
    glDeleteProgram(shaderProgram);
    //delete models
    glDeleteBuffers(1, &modelDataVBO);
}

void render() {
    //clear screen
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //use the shader
    glUseProgram(shaderProgram);
    
    //enable attributes in program
    glEnableVertexAttribArray(shaderAttribute_coord3D);
    glEnableVertexAttribArray(shaderAttribute_vertexColour);
    
    //describe arrays to program
    glBindBuffer(GL_ARRAY_BUFFER, modelDataVBO);
    glVertexAttribPointer(shaderAttribute_coord3D,  // attribute
                          3,                        // number of elements per vertex, here (x,y)
                          GL_FLOAT,                 // the type of each element
                          GL_FALSE,                 // take our values as-is
                          sizeof(struct modelData), // 2d coord every 5 elements
                          0                         // offset of first element
                          );
    
    glBindBuffer(GL_ARRAY_BUFFER, modelDataVBO);
    glVertexAttribPointer(shaderAttribute_vertexColour, // attribute
                          3,                            // number of elements per vertex, here (r,g,b)
                          GL_FLOAT,                     // the type of each element
                          GL_FALSE,                     // take our values as-is
                          sizeof(struct modelData),     // colour every 5 elements
                          (GLvoid *)(offsetof(struct modelData, colour3D))    // skip 2d coords
                          );
    
    //draw the cube by going through its elements array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelElements);
    int bufferSize;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    glDrawElements(GL_TRIANGLES, bufferSize/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    
    //close up the attribute in program, no more need
    glDisableVertexAttribArray(shaderAttribute_coord3D);
    glDisableVertexAttribArray(shaderAttribute_vertexColour);
    
    //blit drawn screen
    glutSwapBuffers();
}

void reshape(int newWindowWidth, int newWindowHeight)
{
    windowWidth=newWindowWidth;
    windowHeight=newWindowHeight;
    glViewport(0, 0, windowWidth, windowHeight);
}

void idle()
{
    //model matrix using model position vector
    glm::vec3 modelPosition=glm::vec3(0,0,-4);
    glm::mat4 model=glm::translate(glm::mat4(1.0f), modelPosition);
    
    //view matrix using look at
    glm::vec3 cameraPosition=glm::vec3(0,2,0);
    glm::vec3 cameraTarget=glm::vec3(0,0,-4); //same as model position to look at model
    glm::vec3 cameraUp=glm::vec3(0,1,0);
    glm::mat4 view=glm::lookAt(cameraPosition, cameraTarget, cameraUp);
    
    //projection matrix
    GLfloat lensAngle=45.0f;
    GLfloat aspectRatio=1.0*(windowWidth/windowHeight);
    GLfloat nearClippingPlane=0.1f;
    GLfloat farClippingPlane=10.0f;
    glm::mat4 projection=glm::perspective(lensAngle, aspectRatio, nearClippingPlane, farClippingPlane);
    
    glm::mat4 mvp=projection*view*model;
    
    glUniformMatrix4fv(shaderAttribute_uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
    
    //animation matrix
    float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second
    glm::vec3 axis(1.0, -1.0, 0.0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis);
    glUniformMatrix4fv(shaderAttribute_uniform_animation, 1, GL_FALSE, glm::value_ptr(anim));
    
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Voxels");

#ifdef _WIN32
	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK){
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}
#endif

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(initResources()==true){
        glutReshapeFunc(reshape);
        glutDisplayFunc(render);
        glutIdleFunc(idle);
        glutMainLoop();
    }
    
    freeResources();
    return 0;
}