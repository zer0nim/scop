/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 19:18:51 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_vao(u_int32_t *vao_ol, t_obj *obj)
{
	u_int32_t	vbo;

	glGenVertexArrays(2, vao_ol);
	glBindVertexArray(vao_ol[0]);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
\
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj->verts_nb_item * V_STEP, \
	obj->verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
\
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)0);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void	draw_obj(u_int32_t shader, t_vect3 pos, t_vect3 scale, float angle)
{
	t_matrix		*mt_id;
	t_matrix		*trans_m;
	t_matrix		*trans_m2;
	t_matrix		*model;
	int				buff_size;

	glUseProgram(shader);
	mt_id = mt_new(4, 4, TRUE);
	trans_m = mt_translate(mt_id, pos);
	trans_m2 = mt_rotate(trans_m, radians(angle), vect3(0, 1, 0));
	mt_free(&trans_m);
	model = mt_scale(trans_m2, scale);
	mt_free(&trans_m2);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_TRUE, \
	model->cont);
	buff_size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buff_size);
	glDrawArrays(GL_TRIANGLES, 0, buff_size / V_STEP / sizeof(float));
	mt_free(&model);
	mt_free(&mt_id);
}

void	set_shader_mt(u_int32_t shader, t_camera *cam)
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

void	loop_body(GLFWwindow *window, u_int32_t *shader_ol, u_int32_t *vao_ol, \
u_int32_t *dif_spec)
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
		vect3(1.0f, 0.0f, 1.0f)
	};
	char			buff[128];

	cam = &(((t_win_user *)glfwGetWindowUserPointer(window))->cam);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_ol[0]);
	glBindVertexArray(vao_ol[0]);
	glUniform3fv(glGetUniformLocation(shader_ol[0], "viewPos"), 1, \
	&(cam->pos.x));

	glUniform1f(glGetUniformLocation(shader_ol[0], "material.shininess"), \
	32.0f);

	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.direction"), \
	-0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.ambient"), \
	0.05, 0.05, 0.05);
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.diffuse"), \
	0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "dirLight.specular"), \
	1.0f, 1.0f, 1.0f);

	i = -1;
	while (++i < 4)
	{
		snprintf(buff, sizeof(buff), "pointLights[%d].position", i);
		glUniform3fv(glGetUniformLocation(shader_ol[0], buff), 1, \
		&(point_light_pos[i].x));
		snprintf(buff, sizeof(buff), "pointLights[%d].constant", i);
		glUniform1f(glGetUniformLocation(shader_ol[0], buff), 1.0f);
		snprintf(buff, sizeof(buff), "pointLights[%d].linear", i);
		glUniform1f(glGetUniformLocation(shader_ol[0], buff), 0.045f);
		snprintf(buff, sizeof(buff), "pointLights[%d].quadratic", i);
		glUniform1f(glGetUniformLocation(shader_ol[0], buff), 0.0075f);
		snprintf(buff, sizeof(buff), "pointLights[%d].ambient", i);
		glUniform3f(glGetUniformLocation(shader_ol[0], buff), 0.05, 0.05, 0.05);
		snprintf(buff, sizeof(buff), "pointLights[%d].diffuse", i);
		glUniform3fv(glGetUniformLocation(shader_ol[0], buff), 1, \
		&(point_light_color[i].x));
		snprintf(buff, sizeof(buff), "pointLights[%d].specular", i);
		glUniform3f(glGetUniformLocation(shader_ol[0], buff), 1.0f, 1.0f, 1.0f);
	}

	glUniform3fv(glGetUniformLocation(shader_ol[0], "spotLight.position"), 1, \
	&(cam->pos.x));
	glUniform3fv(glGetUniformLocation(shader_ol[0], "spotLight.direction"), 1, \
	&(cam->front.x));
	glUniform1f(glGetUniformLocation(shader_ol[0], "spotLight.cutOff"), \
	cos(radians(12.5f)));
	glUniform1f(glGetUniformLocation(shader_ol[0], "spotLight.outerCutOff"), \
	cos(radians(15.0f)));
	glUniform1f(glGetUniformLocation(shader_ol[0], "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader_ol[0], "spotLight.linear"), 0.045f);
	glUniform1f(glGetUniformLocation(shader_ol[0], "spotLight.quadratic"), \
	0.0075f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "spotLight.ambient"), \
	0.05, 0.05, 0.05);
	glUniform3f(glGetUniformLocation(shader_ol[0], "spotLight.diffuse"), \
	0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(shader_ol[0], "spotLight.specular"), \
	1.0f, 1.0f, 1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dif_spec[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dif_spec[1]);

	set_shader_mt(shader_ol[0], cam);

	// draw_cubes(shader_ol);
	draw_obj(shader_ol[0], vect3(0.0f, 0.0f, 0.0f), vect3(1.0f, 1.0f, 1.0f), \
	0.0f);

	glUseProgram(shader_ol[1]);
	glBindVertexArray(vao_ol[1]);
	set_shader_mt(shader_ol[1], cam);
	i = -1;
	while (++i < 4)
	{
		glUniform3fv(glGetUniformLocation(shader_ol[1], "color"), 1, \
		&(point_light_color[i].x));
		draw_obj(shader_ol[1], point_light_pos[i], vect3(0.2f, 0.2f, 0.2f), \
		0.0f);
	}

	glBindVertexArray(0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int8_t	init(GLFWwindow *window, u_int32_t *shader_ol, u_int32_t *vao_ol, \
u_int32_t *dif_spec, const char *argv[])
{
	t_win_user	*win_u;
	t_obj		obj;

	if (!parse_obj(argv[1], &obj))
		return (FALSE);
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
	init_vao(vao_ol, &obj);
	free_obj(&obj);
	if (!(load_texture("/Users/emarin/Downloads/container2.tga", dif_spec)))
		return (FALSE);
	if (!(load_texture("/Users/emarin/Downloads/container2_specular.tga", \
	dif_spec + 1)))
		return (FALSE);
	glUseProgram(shader_ol[0]);
	glUniform1i(glGetUniformLocation(shader_ol[0], "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(shader_ol[0], "material.specular"), 1);
	return (TRUE);
}

int		main(int argc, const char *argv[])
{
	u_int32_t	vao_obj_light[2];
	t_win_user	win_u;
	GLFWwindow	*window;
	u_int32_t	shader_ol[2];
	u_int32_t	dif_spec[3];

	if (argc != 2)
	{
		printf("usage: ./scop file.obj\n");
		return (1);
	}

	if (!init_window(&window, "Scop"))
		return (FALSE);

	glfwSetWindowUserPointer(window, &win_u);
	if (!init(window, shader_ol, vao_obj_light, dif_spec, argv))
		return (1);
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		loop_body(window, shader_ol, vao_obj_light, dif_spec);
	}
	glDeleteProgram(shader_ol[0]);
	glDeleteProgram(shader_ol[1]);
	glDeleteVertexArrays(2, vao_obj_light);
	glfwTerminate();
	return (0);
}
