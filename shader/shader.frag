#version 410 core

out vec4 outColor;

in vec2 outTexcoord;

uniform sampler2D Texture;
uniform vec4 color;
uniform vec4 keycolor;

#define FloatEpsilon 0.001

bool FloatEq(float a, float b) {
    return abs(a - b) <= FloatEpsilon;
}

void main() {
    vec4 finalColor = texture(Texture, outTexcoord);
    if (FloatEq(finalColor.r, keycolor.r) &&
        FloatEq(finalColor.g, keycolor.g) &&
        FloatEq(finalColor.b, keycolor.b)) {
        discard;
    }
    outColor = vec4(finalColor.rgb * color.rgb, 1);
}
