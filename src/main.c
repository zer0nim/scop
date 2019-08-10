/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/09 15:56:51 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	initVao(unsigned int *vao) {
	// pos			color:
	// x, y, z,  	r, g, b
	float vertices[] = {
		0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,		// top right
		0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,		// bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f		// top left
	};
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	// copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	// copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// then set our vertex colors attributes pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

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

void	loopBody(GLFWwindow* window, unsigned int shader_program, unsigned int vao) {
	processInput(window);

	// clear the screen
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

	// drawing code
	glUseProgram(shader_program);
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

	unsigned int shader_program = 0;
	if (!create_shader(&shader_program))
		return 1;

	unsigned int vao;
	initVao(&vao);

	while (!glfwWindowShouldClose(window))
		loopBody(window, shader_program, vao);

	glDeleteProgram(shader_program);

	glfwTerminate();
	return 0;
}
