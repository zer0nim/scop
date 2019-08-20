#version 410 core
out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    float   ambient_strgh = 0.1;
    vec3    ambient = ambient_strgh * lightColor;
    vec3 result = ambient * objectColor;
    fragColor = vec4(result, 1.0);
}
