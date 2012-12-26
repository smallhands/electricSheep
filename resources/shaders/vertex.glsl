attribute vec3 coord3D;
attribute vec3 vertexColour;
attribute vec3 normal;

uniform mat4 model;
uniform mat4 inverseTransposeModel;

uniform mat4 view;
uniform mat4 projection;

varying lowp vec3 fragColor;

struct lightSource
{
  vec4 position;
  vec4 diffuse;
};
lightSource light0 = lightSource(
    vec4(1.0, 1.0, 1.0, 0.0),
    vec4(1.0, 1.0, 1.0, 1.0)
);

void main(void){
    vec3 normalDirection = vec3(normalize(inverseTransposeModel * vec4(normal, 1.0)));

    vec3 lightDirection = normalize(vec3(light0.position));

    fragColor = (vec3(light0.diffuse) * vertexColour * max(0.0, dot(normalDirection, lightDirection))) + vec3(vertexColour.x*0.1, vertexColour.y*0.1, vertexColour.z*0.1);

    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(coord3D, 1.0);
}