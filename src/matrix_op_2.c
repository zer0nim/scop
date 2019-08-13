/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:52:59 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 14:26:26 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"

void		mt_add(t_matrix *mt, float add_v)
{
	int			i;
	int			j;

	i = -1;
	while (++i < mt->h)
	{
		j = -1;
		while (++j < mt->h)
			mt->cont[i][j] += add_v;
	}
}

void		mt_scalar_prod(t_matrix *mt, float scalar_v)
{
	int			i;
	int			j;

	i = -1;
	while (++i < mt->h)
	{
		j = -1;
		while (++j < mt->h)
			mt->cont[i][j] *= scalar_v;
	}
}
