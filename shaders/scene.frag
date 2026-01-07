#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform vec4 colour;
uniform sampler2D textureSampler;
uniform int useTexture;

void main() {
    if (useTexture == 1) {
        vec4 texColour = texture(textureSampler, TexCoord);
        FragColor = texColour * colour;  // colour acts as tint
    } else {
        FragColor = colour;
    }
}
