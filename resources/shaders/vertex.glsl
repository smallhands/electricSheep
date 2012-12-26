attribute vec3 coord3D;
attribute vec3 vertexColour;
attribute vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying lowp vec3 fragColor;

void main(void){
   mat4 mvp = projection * view * model;

   gl_Position = mvp * vec4(coord3D, 1.0);
   
   vec4 worldspaceNormal = mvp * vec4(normal, 1.0);

   fragColor = vec3(vertexColour.x + worldspaceNormal.x, vertexColour.y + worldspaceNormal.y, vertexColour.z + worldspaceNormal.z);
}