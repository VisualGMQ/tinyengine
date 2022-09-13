std::string VertexShaderSource = R"(
#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexcoord;

out vec2 outTexcoord;

uniform mat4 project;
uniform mat4 model;
uniform mat4 view;

void main() {
    outTexcoord = inTexcoord;
    gl_Position = project * view * model * vec4(inPosition, 1);
}
)";

std::string FragShaderSource = R"(
#version 410 core

out vec4 outColor;

in vec2 outTexcoord;

uniform sampler2D Texture;
uniform vec4 color;

void main() {
    outColor = color * texture(Texture, outTexcoord);
}
)";
