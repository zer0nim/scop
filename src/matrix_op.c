/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:52:59 by emarin            #+#    #+#             */
/*   Updated: 2019/08/12 17:14:33 by emarin           ###   ########.fr       */
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
