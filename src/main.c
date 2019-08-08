/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/08 14:59:52 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <stdio.h>

const unsigned int SCREEN_W = 1024;
const unsigned int SCREEN_H = 576;

const char *VERTEX_SHADER_SRC = "\
#version 410 core\n\
layout (location = 0) in vec3 aPos;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(aPos, 1.0);\n\
}";

const char *FRAGMENT_SHADER_SRC = "\
#version 410 core\n\
out vec4 FragColor;\n\
\n\
void main()\n\
{\n\
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}";

void	initVao(unsigned int *vao) {
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenVertexArrays(1, vao);
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	glBindVertexArray(*vao);

	// copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered vbo as the vertex attribute's bound
	// vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the vao afterwards so other vao calls won't accidentally modify this vao
	// , but this rarely happens.
	// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't
	// unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// to draw in wireframe mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

char	createShader(unsigned int *vertexShader, unsigned int *fragmentShader, unsigned int *shaderProgram) {
	*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertexShader, 1, &VERTEX_SHADER_SRC, NULL);
	glCompileShader(*vertexShader);
	// check for compilation errors
	int  success;
	char infoLog[512];
	glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		return FALSE;
	}

	*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentShader, 1, &FRAGMENT_SHADER_SRC, NULL);
	glCompileShader(*fragmentShader);
	// check for compilation errors
	glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		return FALSE;
	}

	*shaderProgram = glCreateProgram();
	// link the shader objects
	glAttachShader(*shaderProgram, *vertexShader);
	glAttachShader(*shaderProgram, *fragmentShader);
	glLinkProgram(*shaderProgram);
	// check for linking errors
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::LINKING_FAILED\n%s\n", infoLog);
		return FALSE;
	}

	// delete the shader objects because
	// after linking we don't neeed them anymore
	glDeleteShader(*vertexShader);
	glDeleteShader(*fragmentShader);
	return TRUE;
}

void	processInput(GLFWwindow *window) {
	// close windows on escape
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}

// called on windows resize
void	framebufferResizeCb(GLFWwindow* window, int width, int height) {
	(void)window;
	// tell OpenGL the size of the rendering window
    glViewport(0, 0, width, height);
}

char	initWindows(GLFWwindow	**window) {
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "Could not start glfw3\n");
		return FALSE;
	}

	// manage the windows options
	// select opengl version 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the windows
	*window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Scop", NULL, NULL);
	if (!(*window)) {
		fprintf(stderr, "Fail to create glfw3 window\n");
		glfwTerminate();
		return FALSE;
	}
	glfwMakeContextCurrent(*window);
	// call framebufferResizeCb func on windows resize
	glfwSetFramebufferSizeCallback(*window, framebufferResizeCb);
	return TRUE;
}

void	loopBody(GLFWwindow* window, unsigned int shaderProgram, unsigned int vao) {
	processInput(window);

	// clear the screen
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

	// drawing code
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Swap front and back buffers
	glfwSwapBuffers(window);
	// Poll for and process events
	glfwPollEvents();
}

int		main() {
	GLFWwindow* window;
	if (!initWindows(&window))
		return 1;

	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	unsigned int shaderProgram = 0;
	if (!createShader(&vertexShader, &fragmentShader, &shaderProgram))
		return 1;

	unsigned int vao;
	initVao(&vao);

	while (!glfwWindowShouldClose(window))
		loopBody(window, shaderProgram, vao);

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
