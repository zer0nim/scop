/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/07 18:01:19 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void processInput(GLFWwindow *window) {
	// close windows on escape
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}

// called on windows resize
void framebufferResizeCb(GLFWwindow* window, int width, int height) {
	(void)window;
    glViewport(0, 0, width, height);
}

int main() {
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
	GLFWwindow* window = glfwCreateWindow(1024, 576, "Scop", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Fail to create glfw3 window\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// tell OpenGL the size of the rendering window
	glViewport(0, 0, 800, 600);
	// call framebufferResizeCb func on windows resize
	glfwSetFramebufferSizeCallback(window, framebufferResizeCb);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// clear the screen
		glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
