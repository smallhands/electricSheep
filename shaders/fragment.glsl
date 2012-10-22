varying vec3 fragmentColour;

void main(void) {
    gl_FragColor = vec4(fragmentColour.x, fragmentColour.y, fragmentColour.z, 1.0);
}