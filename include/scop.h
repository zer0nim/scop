/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:28:11 by emarin            #+#    #+#             */
/*   Updated: 2019/09/19 14:33:54 by emarin           ###   ########.fr       */
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

float			radians(float degree_angle);
float			degrees(float radian_angle);

typedef struct	s_win_user
{
	t_camera	cam;
	float		dt_time;
	float		last_frame;
}				t_win_user;

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

#endif
