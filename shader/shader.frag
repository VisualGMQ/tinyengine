#version 410 core

out vec4 outColor;

in vec2 outTexcoord;

uniform sampler2D Texture;
uniform vec4 color;

void main() {
    outColor = color * texture(Texture, outTexcoord);
}
