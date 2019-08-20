/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/20 16:21:32 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const float		g_verts[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
\
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
\
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
\
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
\
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
\
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

void	init_vao(unsigned int *vao)
{
	unsigned int vbo;

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
\
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_verts), g_verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
\
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
\
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), \
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
\
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void	draw_cubes(t_matrix *mt_id, unsigned int shader_prog)
{
	int				i;
	t_matrix		*model;
	t_matrix		*trans_m;
	t_vect3			cube_pos[7];
	unsigned int	model_loc;

	cube_pos[0] = vect3(0.0f, 0.0f, 0.0f);
	cube_pos[1] = vect3(2.0f, 5.0f, -15.0f);
	cube_pos[2] = vect3(-1.5f, -2.2f, -2.5f);
	cube_pos[3] = vect3(-3.8f, -2.0f, -12.3f);
	cube_pos[4] = vect3(2.4f, -0.4f, -3.5f);
	cube_pos[5] = vect3(-1.7f, 3.0f, -7.5f);
	cube_pos[6] = vect3(1.3f, -2.0f, -2.5f);
	i = -1;
	while (++i < 7)
	{
		trans_m = mt_translate(mt_id, cube_pos[i]);
		model = mt_rotate(trans_m, radians(20.0f * i), vect3(1.0f, 0.3f, 0.5f));
		mt_free(&trans_m);
		model_loc = glGetUniformLocation(shader_prog, "model");
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, model->cont);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		mt_free(&model);
	}
	mt_free(&mt_id);
}

void	loop_body(GLFWwindow *window, unsigned int shader_prog, \
unsigned int vao, unsigned int *textures)
{
	t_camera		*cam;
	t_matrix		*mt;
	unsigned int	mt_loc;

	cam = &(((t_win_user *)glfwGetWindowUserPointer(window))->cam);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	mt = mt_look_at(cam->pos, v3_add(cam->pos, cam->front), cam->up);
	mt_loc = glGetUniformLocation(shader_prog, "view");
	glUniformMatrix4fv(mt_loc, 1, GL_TRUE, mt->cont);
	mt_free(&mt);
	mt = mt_perspective(radians(45.0f), (float)SCREEN_W / \
	(float)SCREEN_H, 0.1f, 100.0f);
	mt_loc = glGetUniformLocation(shader_prog, "projection");
	glUniformMatrix4fv(mt_loc, 1, GL_TRUE, mt->cont);
	mt_free(&mt);
	draw_cubes(mt_new(4, 4, TRUE), shader_prog);
	glBindVertexArray(0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int8_t	init(GLFWwindow *window, unsigned int *shader_prog, \
unsigned int *vao, unsigned int *textures)
{
	t_win_user *win_u;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	cam_init(&(win_u->cam));
	win_u->dt_time = 0.0f;
	win_u->last_frame = 0.0f;
	if (!create_shader(shader_prog))
		return (FALSE);
	init_vao(vao);
	if (!(load_texture("/Users/emarin/Downloads/container.tga", textures)))
		return (FALSE);
	if (!(load_texture("/Users/emarin/Downloads/awesome_face.tga", \
	textures + 1)))
		return (FALSE);
	return (TRUE);
}

int		main(void)
{
	unsigned int	vao;
	t_win_user		win_u;
	GLFWwindow		*window;
	unsigned int	shader_prog;
	unsigned int	textures[2];

	if (!init_window(&window, "Scop"))
		return (FALSE);
	glfwSetWindowUserPointer(window, &win_u);
	if (!init(window, &shader_prog, &vao, textures))
		return (1);
	glUseProgram(shader_prog);
	glUniform1i(glGetUniformLocation(shader_prog, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader_prog, "texture2"), 1);
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		loop_body(window, shader_prog, vao, textures);
	}
	glDeleteProgram(shader_prog);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
	return (0);
}
