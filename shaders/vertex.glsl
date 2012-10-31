attribute vec3 coord3D;

uniform mat4 mvp;

attribute vec2 TexCoordIn;
varying vec2 TexCoordOut;

void main(void){
   gl_Position=mvp*vec4(coord3D, 1.0);
   TexCoordOut = TexCoordIn;
}