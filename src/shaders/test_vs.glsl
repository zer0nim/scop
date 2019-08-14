#version 410 core
layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec2 vertTexCoord;

out vec3 color;
out vec2 texCoord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(vertPos, 1.0);
	color = vertColor;
	texCoord = vertTexCoord;
}
