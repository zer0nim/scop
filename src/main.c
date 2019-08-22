/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/08/22 21:02:59 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**	positions		normals		texture coords
*/
const float		g_verts[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
\
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
\
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
\
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
\
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
\
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), \
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(float), \
	(void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
\
	glBindVertexArray(vao_ol[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
\
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void	draw_cube(unsigned int shader, t_vect3 pos, t_vect3 scale, \
float angle, t_vect3 axis_v)
{
	t_matrix		*mt_id;
	t_matrix		*trans_m;
	t_matrix		*trans_m2;
	t_matrix		*model;

	glUseProgram(shader);
	mt_id = mt_new(4, 4, TRUE);
	trans_m = mt_translate(mt_id, pos);
	trans_m2 = mt_rotate(trans_m, radians(angle), axis_v);
	mt_free(&trans_m);
	model = mt_scale(trans_m2, scale);
	mt_free(&trans_m2);
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

void	draw_cubes(unsigned int *shader_ol)
{
	int				i;
	t_vect3			cube_pos[7];

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
		draw_cube(shader_ol[0], cube_pos[i], vect3(1.0f, 1.0f, 1.0f), \
		20.0f * i, vect3(1.0f, 0.3f, 0.5f));
	}
}

void	loop_body(GLFWwindow *window, unsigned int *shader_ol, \
unsigned int *vao_ol, unsigned int *dif_spec_map)
{
	t_camera		*cam;
	int				i;
	t_vect3			point_light_pos[] = {
		vect3(0.7f, 0.2f, 2.0f),
		vect3(2.3f, -3.3f, -4.0f),
		vect3(-4.0f, 2.0f, -12.0f),
		vect3(0.0f, 0.0f, -3.0f)
	};
	t_vect3			point_light_color[] = {
		vect3(1.0f, 0.0f, 0.0f),
		vect3(0.0f, 1.0f, 0.0f),
		vect3(0.0f, 0.0f, 1.0f),
		vect3(1.0f, 1.0f, 0.0f)
	};


	cam = &(((t_win_user *)glfwGetWindowUserPointer(window))->cam);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_ol[0]);
	glBindVertexArray(vao_ol[0]);
	glUniform3fv(glGetUniformLocation(shader_ol[0], "viewPos"), 1, \
	&(cam->pos.x));
\
	glUniform1f(glGetUniformLocation(shader_ol[0], "material.shininess"), \
	32.0f);
\
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.direction"), \
	-0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.ambient"), \
	0.05, 0.05, 0.05);
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.diffuse"), \
	0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.specular"), \
	1.0f, 1.0f, 1.0f);
\
	i = -1;
	while (++i < 4)
	{
		glUniform3fv(glGetUniformLocation(shader_ol[0], "pointLights[i].position"), 1, \
		&(point_light_pos[i].x));
		glUniform1f(glGetUniformLocation(shader_ol[0], "pointLights[i].constant"), \
		1.0f);
		glUniform1f(glGetUniformLocation(shader_ol[0], "pointLights[i].linear"), \
		0.045f);
		glUniform1f(glGetUniformLocation(shader_ol[0], "pointLights[i].quadratic"), \
		0.0075f);
		glUniform3f(glGetUniformLocation(shader_ol[0], "pointLights[i].ambient"), \
		0.05, 0.05, 0.05);
		glUniform3fv(glGetUniformLocation(shader_ol[0], "pointLights[i].diffuse"), 1, \
		&(point_light_color[i].x));
		glUniform3f(glGetUniformLocation(shader_ol[0], "pointLights[i].specular"), \
		1.0f, 1.0f, 1.0f);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dif_spec_map[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dif_spec_map[1]);
	// glActiveTexture(GL_TEXTURE2);
	// glBindTexture(GL_TEXTURE_2D, dif_spec_map[2]);
\
	set_shader_mt(shader_ol[0], cam);
	draw_cubes(shader_ol);
	// draw_cube(shader_ol[0], vect3(0.0f, 0.0f, 0.0f), vect3(1.0f, 1.0f, 1.0f));
	glUseProgram(shader_ol[1]);
	glBindVertexArray(vao_ol[1]);
	set_shader_mt(shader_ol[1], cam);
	i = -1;
	while (++i < 4)
	{
		draw_cube(shader_ol[1], point_light_pos[i], vect3(0.2f, 0.2f, 0.2f), 0, \
		vect3(1.0f, 0.0f, 0.0f));
	}
\
	glBindVertexArray(0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int8_t	init(GLFWwindow *window, unsigned int *shader_ol, \
unsigned int *vao_ol, unsigned int *dif_spec_map)
{
	t_win_user		*win_u;

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
	if (!(load_texture("/Users/emarin/Downloads/container2.tga", dif_spec_map)))
		return (FALSE);
	if (!(load_texture("/Users/emarin/Downloads/container2_specular.tga", \
	dif_spec_map + 1)))
		return (FALSE);
	if (!(load_texture("/Users/emarin/Downloads/container2_emission.tga", \
	dif_spec_map + 2)))
		return (FALSE);
	glUseProgram(shader_ol[0]);
	glUniform1i(glGetUniformLocation(shader_ol[0], "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(shader_ol[0], "material.specular"), 1);
	glUniform1i(glGetUniformLocation(shader_ol[0], "material.emission"), 2);
	return (TRUE);
}

int		main(void)
{
	unsigned int	vao_obj_light[2];
	t_win_user		win_u;
	GLFWwindow		*window;
	unsigned int	shader_ol[2];
	unsigned int	dif_spec_map[3];

	if (!init_window(&window, "Scop"))
		return (FALSE);
	glfwSetWindowUserPointer(window, &win_u);
	if (!init(window, shader_ol, vao_obj_light, dif_spec_map))
		return (1);
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		loop_body(window, shader_ol, vao_obj_light, dif_spec_map);
	}
	glDeleteProgram(shader_ol[0]);
	glDeleteProgram(shader_ol[1]);
	glDeleteVertexArrays(2, vao_obj_light);
	glfwTerminate();
	return (0);
}
