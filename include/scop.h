/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:28:11 by emarin            #+#    #+#             */
/*   Updated: 2019/08/26 17:01:27 by emarin           ###   ########.fr       */
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

#endif
