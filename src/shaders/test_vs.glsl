#version 410 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec2 vertTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(vertPos, 1.0);
	texCoord = vertTexCoord;
}