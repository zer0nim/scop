/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:52:59 by emarin            #+#    #+#             */
/*   Updated: 2019/08/12 18:36:53 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"

t_matrix	*mt_mul(t_matrix *lhs, t_matrix *rhs)
{
	t_matrix	*res;
	int			i;
	int			j;
	int			k;

	if (lhs->w != rhs->h)
	{
		fprintf(stderr, "to multiply matrix, lhs width has to be equal \
		to the rhs height");
		return (NULL);
	}
	if (!(res = mt_new(rhs->h, rhs->w, FALSE)))
		return (NULL);
	i = -1;
	while (++i < lhs->h)
	{
		j = -1;
		while (++j < rhs->h)
		{
			k = -1;
			while (++k < lhs->w)
				res->cont[i][j] += lhs->cont[i][k] * rhs->cont[k][j];
		}
	}
	return (res);
}

void		mt_add(t_matrix *mt, float add_v)
{
	int			i;
	int			j;

	if (mt)
	{
		i = -1;
		while (++i < mt->h)
		{
			j = -1;
			while (++j < mt->h)
				mt->cont[i][j] += add_v;
		}
	}
}

void		mt_scalar_prod(t_matrix *mt, float scalar_v)
{
	int			i;
	int			j;

	if (mt)
	{
		i = -1;
		while (++i < mt->h)
		{
			j = -1;
			while (++j < mt->h)
				mt->cont[i][j] *= scalar_v;
		}
	}
}
