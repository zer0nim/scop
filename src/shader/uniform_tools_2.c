/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:57:25 by emarin            #+#    #+#             */
/*   Updated: 2019/09/19 14:35:05 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_mat2_sh(u_int32_t shader, const char *name, const t_matrix *mat)
{
	glUniformMatrix2fv(glGetUniformLocation(shader, name), 1, GL_TRUE, \
	mat->cont);
}

void	set_mat3_sh(u_int32_t shader, const char *name, const t_matrix *mat)
{
	glUniformMatrix3fv(glGetUniformLocation(shader, name), 1, GL_TRUE, \
	mat->cont);
}

void	set_mat4_sh(u_int32_t shader, const char *name, const t_matrix *mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_TRUE, \
	mat->cont);
}
