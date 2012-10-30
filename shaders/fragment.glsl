varying vec3 fragmentColour;

varying lowp vec2 TexCoordOut;
uniform sampler2D Texture;

void main(void) {
    gl_FragColor = fragmentColour * texture2D(Texture,TexCoordOut);
}