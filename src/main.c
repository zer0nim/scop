/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/07 22:20:12 by emarin           ###   ########.fr       */
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
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
}";

const char *FRAGMENT_SHADER_SRC = "\
#version 410 core\n\
out vec4 FragColor;\n\
\n\
void main()\n\
{\n\
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}";

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

int		main() {
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "Could not start glfw3\n");
		return 1;
	}

	// manage the windows options
	// select opengl version 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the windows
	GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Scop", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Fail to create glfw3 window\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	// call framebufferResizeCb func on windows resize
	glfwSetFramebufferSizeCallback(window, framebufferResizeCb);


	// v___shader___________________________________________

	// create vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VERTEX_SHADER_SRC, NULL);
	glCompileShader(vertexShader);
	// check for compilation errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
		return FALSE;
	}

	// create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SRC, NULL);
	glCompileShader(fragmentShader);
	// check for compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
		return FALSE;
	}

	// create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// link the shader objects
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "ERROR::SHADER::LINKING_FAILED\n%s\n", infoLog);
		return FALSE;
	}

	// delete the shader objects because
	// after linking we don't neeed them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ^___shader___________________________________________


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind vertex array object, then bind and set vertex buffers
	//, and then configure vertex attributess
	glBindVertexArray(VAO);

	// copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// store the vertex data within memory on the graphics card
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound
	// vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO
	// , but this rarely happens.
	// Modifying other VAOs requires a call to glBindVertexArray anyways so we generally don't
	// unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// clear the screen
		glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

		// draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
