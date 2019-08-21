/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/21 17:48:31 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const float		g_verts[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
\
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
\
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
\
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
\
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
\
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

void	init_vao(unsigned int *vao_ol)
{
	unsigned int vbo;

	glGenVertexArrays(2, vao_ol);
	glBindVertexArray(vao_ol[0]);
\
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_verts), g_verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
\
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), \
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
\
	glBindVertexArray(vao_ol[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
\
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void	draw_cube(unsigned int shader, t_vect3 pos, t_vect3 scale)
{
	t_matrix		*mt_id;
	t_matrix		*trans_m;
	t_matrix		*model;

	glUseProgram(shader);
	mt_id = mt_new(4, 4, TRUE);
	trans_m = mt_translate(mt_id, pos);
	model = mt_scale(trans_m, scale);
	mt_free(&trans_m);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_TRUE, \
	model->cont);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mt_free(&model);
	mt_free(&mt_id);
}

void	set_shader_mt(unsigned int shader, t_camera *cam)
{
	t_matrix		*mt;

	glUseProgram(shader);
	mt = mt_look_at(cam->pos, v3_add(cam->pos, cam->front), cam->up);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE, \
	mt->cont);
	mt_free(&mt);
	mt = mt_perspective(radians(45.0f), (float)SCREEN_W / \
	(float)SCREEN_H, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_TRUE, \
	mt->cont);
	mt_free(&mt);
}

void	loop_body(GLFWwindow *window, unsigned int *shader_ol, \
unsigned int *vao_ol)
{
	t_camera		*cam;
	t_vect3			ligh_pos;

	glUseProgram(shader_ol[0]);
	ligh_pos = vect3(2.0f * sin(glfwGetTime()), 0, 1.5f * cos(glfwGetTime()));
	cam = &(((t_win_user *)glfwGetWindowUserPointer(window))->cam);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao_ol[0]);
	glUniform3f(glGetUniformLocation(shader_ol[0], "objectColor"), \
	1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "lightColor"), \
	1.0f, 1.0f, 1.0f);
	glUniform3fv(glGetUniformLocation(shader_ol[0], "lightPos"), 1, \
	&(ligh_pos.x));
	glUniform3fv(glGetUniformLocation(shader_ol[0], "viewPos"), 1, \
	&(cam->pos.x));
\
	set_shader_mt(shader_ol[0], cam);
	draw_cube(shader_ol[0], vect3(0.0f, 0.0f, 0.0f), vect3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(vao_ol[1]);
	glUseProgram(shader_ol[1]);
	set_shader_mt(shader_ol[1], cam);
	draw_cube(shader_ol[1], ligh_pos, vect3(0.2f, 0.2f, 0.2f));
\
	glBindVertexArray(0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int8_t	init(GLFWwindow *window, unsigned int *shader_ol, \
unsigned int *vao_ol)
{
	t_win_user *win_u;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	cam_init(&(win_u->cam));
	win_u->dt_time = 0.0f;
	win_u->last_frame = 0.0f;
	if (!create_shader(shader_ol, "../src/shader/obj_vs.glsl", \
	"../src/shader/obj_fs.glsl"))
		return (FALSE);
	if (!create_shader(shader_ol + 1, "../src/shader/light_vs.glsl", \
	"../src/shader/light_fs.glsl"))
		return (FALSE);
	init_vao(vao_ol);
	return (TRUE);
}

int		main(void)
{
	unsigned int	vao_obj_light[2];
	t_win_user		win_u;
	GLFWwindow		*window;
	unsigned int	shader_ol[2];

	if (!init_window(&window, "Scop"))
		return (FALSE);
	glfwSetWindowUserPointer(window, &win_u);
	if (!init(window, shader_ol, vao_obj_light))
		return (1);
	glUseProgram(shader_ol[0]);
	glUniform1i(glGetUniformLocation(shader_ol[0], "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader_ol[0], "texture2"), 1);
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		loop_body(window, shader_ol, vao_obj_light);
	}
	glDeleteProgram(shader_ol[0]);
	glDeleteProgram(shader_ol[1]);
	glDeleteVertexArrays(2, vao_obj_light);
	glfwTerminate();
	return (0);
}
