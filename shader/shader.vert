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
    // gl_Position = vec4(inPosition, 1);
}
