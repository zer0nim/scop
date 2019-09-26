/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:55:36 by emarin            #+#    #+#             */
/*   Updated: 2019/09/26 14:24:03 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_vao(t_data_3d *data_3d)
{
	glGenVertexArrays(2, &(data_3d->vao_obj));
	glBindVertexArray(data_3d->vao_obj);
	glGenBuffers(1, &(data_3d->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, data_3d->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data_3d->obj.verts_nb_item * \
	V_STEP, data_3d->obj.verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_3d->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), \
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 11 * sizeof(float), \
	(void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), \
	(void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
\
	glBindVertexArray(data_3d->vao_light);
	glBindBuffer(GL_ARRAY_BUFFER, data_3d->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), \
	(void*)0);
	glEnableVertexAttribArray(0);
}

void	init_win_u(t_win_user *win_u, int8_t first_call)
{
	t_setting	*settings;

	if (first_call)
	{
		win_u->dt_time = 0.0f;
		win_u->last_frame = 0.0f;
		win_u->width = SCREEN_W;
		win_u->height = SCREEN_H;
	}
\
	cam_init(&(win_u->cam));
	win_u->mix_val = 0.0f;
	win_u->transform = transform(vect3(0.0f, 0.0f, 0.0f), \
	vect3(1.0f, 1.0f, 1.0f), vect3(0.0f, 1.0f, 0.0f), 0.0f);
\
	settings = &(win_u->settings);
	settings->fps_mode = FALSE;
	settings->rotate_mode = TRUE;
	settings->texture_mode = FALSE;
	settings->wireframe_mode = FALSE;
	settings->point_light = FALSE;
	settings->torch_light = FALSE;
}

int8_t	init(t_data_3d *data_3d, GLFWwindow *window)
{
	t_win_user	*win_u;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	init_win_u(win_u, TRUE);
	if (!create_shader(&(data_3d->shad_obj), "src/shader/obj_vs.glsl", \
	"src/shader/obj_fs.glsl") \
	|| !create_shader(&(data_3d->shad_light), "src/shader/light_vs.glsl", \
	"src/shader/light_fs.glsl"))
		return (FALSE);
	init_vao(data_3d);
	free_obj(&(data_3d->obj));
	if (!(load_texture("resource/unicorn.tga", &(data_3d->text_diff))) \
	|| !(load_texture("resource/unicorn_spec.tga", &(data_3d->text_spec))))
		return (FALSE);
	glUseProgram(data_3d->shad_obj);
	set_int_sh(data_3d->shad_obj, "material.diffuse", 0);
	set_int_sh(data_3d->shad_obj, "material.specular", 1);
	set_float_sh(data_3d->shad_obj, "material.shininess", 32.0f);
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
	t_light		lights[NB_POINT_LIGHT];

	srand(time(NULL));
	if (argc != 2)
	{
		printf("usage: ./scop file.obj\n");
		return (1);
	}
\
	if (!parse_obj(argv[1], &(data_3d.obj)) || !(data_3d.obj.verts_nb_item))
		return (FALSE);
	if (!init_window(&window, "Scop"))
		return (FALSE);
	glfwSetWindowUserPointer(window, &win_u);
	if (!init(&data_3d, window))
		return (1);
\
	drawing_loop(&data_3d, window, lights);
\
	free_t_data_3d(&data_3d);
	glfwTerminate();
	return (0);
}
