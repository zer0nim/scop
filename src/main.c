/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/09/19 14:29:49 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_vao(t_data_3d *data_3d)
{
	glGenVertexArrays(2, &(data_3d->vao_obj));
	glBindVertexArray(data_3d->vao_obj);
	glGenBuffers(1, &(data_3d->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, data_3d->vbo);
\
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data_3d->obj.verts_nb_item * \
	V_STEP, data_3d->obj.verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_3d->vbo);
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
	glBindVertexArray(data_3d->vao_light);
	glBindBuffer(GL_ARRAY_BUFFER, data_3d->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void	draw_obj(u_int32_t vbo, u_int32_t shader, t_vect3 pos, t_vect3 scale, \
float angle)
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
	set_mat4_sh(shader, "model", model);
	buff_size = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
	set_mat4_sh(shader, "view", mt);
	mt_free(&mt);
	mt = mt_perspective(radians(45.0f), (float)SCREEN_W / \
	(float)SCREEN_H, 0.1f, 100.0f);
	set_mat4_sh(shader, "projection", mt);
	mt_free(&mt);
}

void	loop_body(t_data_3d *data_3d, GLFWwindow *window)
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
	glUseProgram(data_3d->shad_obj);
	glBindVertexArray(data_3d->vao_obj);
	set_vec3_sh(data_3d->shad_obj, "viewPos", cam->pos);

	set_float_sh(data_3d->shad_obj, "material.shininess", 32.0f);

	set_vec3_sh(data_3d->shad_obj, "dirLight.direction", vect3(-0.2f, -1.0f, -0.3f));
	set_vec3_sh(data_3d->shad_obj, "dirLight.ambient", vect3(0.05, 0.05, 0.05));
	set_vec3_sh(data_3d->shad_obj, "dirLight.diffuse", vect3(0.8f, 0.8f, 0.8f));
	set_vec3_sh(data_3d->shad_obj, "dirLight.specular", vect3(1.0f, 1.0f, 1.0f));

	i = -1;
	while (++i < 4)
	{
		snprintf(buff, sizeof(buff), "pointLights[%d].position", i);
		set_vec3_sh(data_3d->shad_obj, buff, point_light_pos[i]);
		snprintf(buff, sizeof(buff), "pointLights[%d].constant", i);
		set_float_sh(data_3d->shad_obj, buff, 1.0f);
		snprintf(buff, sizeof(buff), "pointLights[%d].linear", i);
		set_float_sh(data_3d->shad_obj, buff, 0.045f);
		snprintf(buff, sizeof(buff), "pointLights[%d].quadratic", i);
		set_float_sh(data_3d->shad_obj, buff, 0.0075f);
		snprintf(buff, sizeof(buff), "pointLights[%d].ambient", i);
		set_vec3_sh(data_3d->shad_obj, buff, vect3(0.05, 0.05, 0.05));
		snprintf(buff, sizeof(buff), "pointLights[%d].diffuse", i);
		set_vec3_sh(data_3d->shad_obj, buff, point_light_color[i]);
		snprintf(buff, sizeof(buff), "pointLights[%d].specular", i);
		set_vec3_sh(data_3d->shad_obj, buff, vect3(1.0f, 1.0f, 1.0f));
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data_3d->text_diff);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data_3d->text_spec);

	set_shader_mt(data_3d->shad_obj, cam);

	draw_obj(data_3d->vbo, data_3d->shad_obj, vect3(0.0f, 0.0f, 0.0f), \
	vect3(1.0f, 1.0f, 1.0f), 0.0f);

	glUseProgram(data_3d->shad_light);
	glBindVertexArray(data_3d->vao_light);
	set_shader_mt(data_3d->shad_light, cam);
	i = -1;
	while (++i < 4)
	{
		set_vec3_sh(data_3d->shad_light, "color", point_light_color[i]);
		draw_obj(data_3d->vbo, data_3d->shad_light, point_light_pos[i], \
		vect3(0.2f, 0.2f, 0.2f), 0.0f);
	}

	glBindVertexArray(0);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

int8_t	init(t_data_3d *data_3d, GLFWwindow *window, const char *obj_name)
{
	t_win_user	*win_u;

	if (!parse_obj(obj_name, &(data_3d->obj)))
		return (FALSE);
	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	cam_init(&(win_u->cam));
	win_u->dt_time = 0.0f;
	win_u->last_frame = 0.0f;
	if (!create_shader(&(data_3d->shad_obj), "../src/shader/obj_vs.glsl", \
	"../src/shader/obj_fs.glsl"))
		return (FALSE);
	if (!create_shader(&(data_3d->shad_light), "../src/shader/light_vs.glsl", \
	"../src/shader/light_fs.glsl"))
		return (FALSE);
	init_vao(data_3d);
	free_obj(&(data_3d->obj));
	if (!(load_texture("/Users/emarin/Downloads/container2.tga", \
	&(data_3d->text_diff))))
		return (FALSE);
	if (!(load_texture("/Users/emarin/Downloads/container2_specular.tga", \
	&(data_3d->text_spec))))
		return (FALSE);
	glUseProgram(data_3d->shad_obj);
	set_int_sh(data_3d->shad_obj, "material.diffuse", 0);
	set_int_sh(data_3d->shad_obj, "material.specular", 1);
	return (TRUE);
}

void	free_t_data_3d(t_data_3d *data_3d)
{
	glDeleteProgram(data_3d->shad_obj);
	glDeleteProgram(data_3d->shad_light);
	glDeleteVertexArrays(2, &(data_3d->vao_obj));
	glDeleteTextures(2, &(data_3d->text_diff));
}

int		main(int argc, const char *argv[])
{
	t_data_3d	data_3d;
	t_win_user	win_u;
	GLFWwindow	*window;

	if (argc != 2)
	{
		printf("usage: ./scop file.obj\n");
		return (1);
	}
	if (!init_window(&window, "Scop"))
		return (FALSE);
\
	glfwSetWindowUserPointer(window, &win_u);
	if (!init(&data_3d, window, argv[1]))
		return (1);
	glClearColor(0.15f, 0.16f, 0.21f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		loop_body(&data_3d, window);
	}
	free_t_data_3d(&data_3d);
	glfwTerminate();
	return (0);
}
