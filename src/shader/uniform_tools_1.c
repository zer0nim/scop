/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_tools_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:57:25 by emarin            #+#    #+#             */
/*   Updated: 2019/09/19 14:34:58 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_int_sh(u_int32_t shader, const char *name, int value)
{
	glUniform1i(glGetUniformLocation(shader, name), value);
}

void	set_float_sh(u_int32_t shader, const char *name, float value)
{
	glUniform1f(glGetUniformLocation(shader, name), value);
}

void	set_vec2_sh(u_int32_t shader, const char *name, const t_vect2 value)
{
	glUniform2fv(glGetUniformLocation(shader, name), 1, &(value.x));
}

void	set_vec3_sh(u_int32_t shader, const char *name, const t_vect3 value)
{
	glUniform3fv(glGetUniformLocation(shader, name), 1, &(value.x));
}

void	set_vec4_sh(u_int32_t shader, const char *name, const t_vect4 value)
{
	glUniform4fv(glGetUniformLocation(shader, name), 1, &(value.x));
}
