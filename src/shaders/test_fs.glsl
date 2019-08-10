#version 410 core
in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    fragColor = mix(texture(texture1, texCoord) * vec4(color, 1), texture(texture2, texCoord), 0.3);
}
