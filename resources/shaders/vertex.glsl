attribute vec3 coord3D;
attribute vec3 vertexColour;

uniform mat4 mvp;

varying lowp vec3 fragColor;

void main(void){
   gl_Position=mvp*vec4(coord3D, 1.0);
   fragColor = vertexColour;
}