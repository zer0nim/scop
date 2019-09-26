/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:28:11 by emarin            #+#    #+#             */
/*   Updated: 2019/09/25 18:41:32 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "define.h"
# include "geometry.h"
# include "parser.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# define NB_POINT_LIGHT 3

# pragma pack(push, 1)

typedef struct	s_data_3d
{
	u_int32_t	vbo;
	u_int32_t	vao_obj;
	u_int32_t	vao_light;
	u_int32_t	shad_obj;
	u_int32_t	shad_light;
	u_int32_t	text_diff;
	u_int32_t	text_spec;
	t_obj		obj;
}				t_data_3d;
# pragma pack(pop)

typedef struct	s_transform
{
	t_vect3	pos;
	t_vect3	scale;
	t_vect3	axis;
	float	angle;
}				t_transform;

typedef struct	s_setting
{
	int8_t		texture_mode;
	int8_t		rotate_mode;
	int8_t		fps_mode;
	int8_t		wireframe_mode;
	int8_t		point_light;
	int8_t		torch_light;
}				t_setting;

typedef struct	s_win_user
{
	t_camera	cam;
	float		dt_time;
	float		last_frame;
	float		mix_val;
	t_transform	transform;
	t_setting	settings;
	float		width;
	float		height;
}				t_win_user;

typedef struct	s_light
{
	t_vect3	pos;
	t_vect3	color;
}				t_light;

int8_t			create_shader(unsigned int *shader_program, char *src_v, \
char *src_f);
void			set_int_sh(u_int32_t shader, const char *name, int value);
void			set_float_sh(u_int32_t shader, const char *name, float value);
void			set_vec2_sh(u_int32_t shader, const char *name, const \
t_vect2 value);
void			set_vec3_sh(u_int32_t shader, const char *name, const \
t_vect3 value);
void			set_vec4_sh(u_int32_t shader, const char *name, const \
t_vect4 value);
void			set_mat2_sh(u_int32_t shader, const char *name, const \
t_matrix *mat);
void			set_mat3_sh(u_int32_t shader, const char *name, const \
t_matrix *mat);
void			set_mat4_sh(u_int32_t shader, const char *name, const \
t_matrix *mat);

int8_t			load_texture(const char *filename, unsigned int *texture);
int8_t			init_window(GLFWwindow	**window, const char *name);
void			process_input(GLFWwindow *window);
void			drawing_loop(t_data_3d *data_3d, GLFWwindow *window, \
t_light *lights);
void			static_lighting(t_data_3d *data_3d, t_light *lights);
void			texture_mix(t_data_3d *data_3d, GLFWwindow *window);
void			fps_input(GLFWwindow *window, t_win_user *win_u, t_camera *cam);
void			translate_input(GLFWwindow *window, t_win_user *win_u);
void			key_callback(GLFWwindow *window, int key, int scancode, \
int action);
void			update_win_title(GLFWwindow *window);
void			rotate_model(t_win_user *win_u);
void			init_win_u(t_win_user *win_u, int8_t first_call);

t_transform		transform(t_vect3 pos, t_vect3 scale, t_vect3 axis, \
float angle);
t_light			light(t_vect3 pos, t_vect3 color);

void			fps_mode(GLFWwindow *window, t_win_user *win_u);
void			wireframe_mode(t_win_user *win_u);
void			torch_lighting_uniform(t_data_3d *data_3d, t_win_user *win_u);

#endif
