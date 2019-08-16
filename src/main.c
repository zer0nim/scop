/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/16 15:41:10 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "tga.h"
#include "matrix.h"

int8_t	load_texture(const char *filename, unsigned int *texture)
{
	t_texture_info	*tga_tex;

	if (!(tga_tex = read_tga_file(filename)))
		return FALSE;

	// generate texture
	glGenTextures(1, &tga_tex->id);
	glBindTexture(GL_TEXTURE_2D, tga_tex->id);
	*texture = tga_tex->id;

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, tga_tex->format, tga_tex->w
	, tga_tex->h, 0, tga_tex->format, GL_UNSIGNED_BYTE, tga_tex->texels);

	glGenerateMipmap(GL_TEXTURE_2D);

	free(tga_tex->texels);
	free(tga_tex);

	return TRUE;
}

int8_t	initVao(unsigned int *vao) {
	// pos			texture coords
	// x, y, z,  	x, y
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	// copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	// then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// then set our vertex texture coordinate attributes pointers
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
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

int8_t	initWindows(GLFWwindow	**window) {
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

void	loopBody(GLFWwindow* window, unsigned int shader_program, unsigned int vao, unsigned int texture1, unsigned int texture2) {
	processInput(window);

	// clear the screen
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

	// drawing code
	glUseProgram(shader_program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	t_matrix	*mt_id = mt_new(4, 4, TRUE);
	t_matrix	*model = mt_rotate(mt_id, (float)glfwGetTime() * radians(50.0f), vect3(0.5f, 1.0f, 0.0f));
	// note that we're translating the scene in the reverse direction of where we want to move
	t_matrix	*view = mt_translate(mt_id, vect3(0.0f, 0.0f, -3.0f));
	t_matrix	*projection = mt_perspective(radians(45.0f), (float)SCREEN_W / (float)SCREEN_H, 0.1f, 100.0f);

	unsigned int model_loc = glGetUniformLocation(shader_program, "model");
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model->cont);
	unsigned int view_loc = glGetUniformLocation(shader_program, "view");
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view->cont);
	unsigned int projection_loc = glGetUniformLocation(shader_program, "projection");
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection->cont);

	mt_free(&projection);
	mt_free(&view);
	mt_free(&model);
	mt_free(&mt_id);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
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
	if (!initVao(&vao))
		return 1;

	unsigned int texture1;
	if (!(load_texture("/Users/emarin/Downloads/container.tga", &texture1)))
		return FALSE;

	unsigned int texture2;
	if (!(load_texture("/Users/emarin/Downloads/awesome_face.tga", &texture2)))
		return FALSE;

	glUseProgram(shader_program);
	glUniform1i(glGetUniformLocation(shader_program, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader_program, "texture2"), 1);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
		loopBody(window, shader_program, vao, texture1, texture2);

	glDeleteProgram(shader_program);
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}
