attribute vec3 coord3D;

attribute vec3 vertexColour;
varying vec3 fragmentColour;

uniform mat4 mvp;
uniform mat4 animation;

attribute vec2 TexCoordIn;
varying vec2 TexCoordOut;

void main(void){
   gl_Position=mvp*animation*vec4(coord3D, 1.0);
   fragmentColour = vertexColour;
   TexCoordOut = TexCoordIn;
}