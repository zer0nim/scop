/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:28:11 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 13:19:37 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "define.h"
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>

int8_t	create_shader(unsigned int *shader_program);

float	deg_to_rad(float degree_angle);
float	rad_to_deg(float radian_angle);

#endif
