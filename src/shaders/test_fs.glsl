#version 410 core
in vec3 color;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main() {
    fragColor = texture(ourTexture, texCoord) * vec4(color, 1.0);
}
