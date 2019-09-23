/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/09/23 18:28:36 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	draw_obj(u_int32_t vbo, u_int32_t shader, t_transform transform)
{
	t_matrix		*mt_id;
	t_matrix		*trans_m;
	t_matrix		*trans_m2;
	t_matrix		*model;
	int				buff_size;

	glUseProgram(shader);
	mt_id = mt_new(4, 4, TRUE);
	trans_m = mt_translate(mt_id, transform.pos);
	trans_m2 = mt_rotate(trans_m, radians(transform.angle), transform.axis);
	mt_free(&trans_m);
	model = mt_scale(trans_m2, transform.scale);
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

void	draw_lights(t_data_3d *data_3d, t_camera *cam, t_light *lights)
{
	int	i;

	glUseProgram(data_3d->shad_light);
	glBindVertexArray(data_3d->vao_light);
	set_shader_mt(data_3d->shad_light, cam);
	i = -1;
	while (++i < NB_POINT_LIGHT)
	{
		set_vec3_sh(data_3d->shad_light, "color", lights[i].color);
		draw_obj(data_3d->vbo, data_3d->shad_light, transform(lights[i].pos, \
		vect3(0.2f, 0.2f, 0.2f), vect3(0.0f, 1.0f, 0.0f), 0.0f));
	}
}

void	texture_mix(t_data_3d *data_3d, GLFWwindow *window)
{
	t_win_user	*win_u;
	float		mix_val;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);

	// printf("win_u->dt_time: %f\n", win_u->dt_time);

	// printf("time: %f\n", glfwGetTime());
    const float frequency = .2;
    mix_val = 0.5f * (1 + sin(2 * M_PI * frequency * glfwGetTime()));
	set_float_sh(data_3d->shad_obj, "mix_val", mix_val);
	// printf("mix_val: %f\n", mix_val);
}

void	loop_body(t_data_3d *data_3d, GLFWwindow *window, t_light *lights)
{
	t_camera	*cam;

	cam = &(((t_win_user *)glfwGetWindowUserPointer(window))->cam);
	glUseProgram(data_3d->shad_obj);
	glBindVertexArray(data_3d->vao_obj);
	set_vec3_sh(data_3d->shad_obj, "viewPos", cam->pos);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data_3d->text_diff);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data_3d->text_spec);
	set_shader_mt(data_3d->shad_obj, cam);
	draw_obj(data_3d->vbo, data_3d->shad_obj, transform(vect3(0.0f, 0.0f, 0.0f)\
	, vect3(1.0f, 1.0f, 1.0f), vect3(0.0f, 1.0f, 0.0f), -90.0f));
\
	texture_mix(data_3d, window);
	draw_lights(data_3d, cam, lights);
}

void	drawing_loop(t_data_3d *data_3d, GLFWwindow *window, t_light *lights)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	static_lighting(data_3d, lights);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		loop_body(data_3d, window, lights);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}