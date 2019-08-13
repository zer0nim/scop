/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:52:59 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 13:05:32 by emarin           ###   ########.fr       */
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

t_matrix	*mt_scale(t_matrix *mt, t_matrix *scale_vect)
{
	t_matrix	*scale_mt;
	t_matrix	*res;

	if (!(scale_vect->h == 3 && scale_vect->w == 1
	&& mt->w == 4 && mt->h == 4))
	{
		if (mt->w != 4 || mt->h != 4)
			fprintf(stderr, "mt need to be a 4x4 matrix");
		else
			fprintf(stderr, "scale_vect need to be a 3x1 matrix");
		return (NULL);
	}
	if (!(scale_mt = mt_new(mt->h, mt->w, TRUE)))
		return (NULL);
	scale_mt->cont[0][0] = scale_vect->cont[0][0];
	scale_mt->cont[1][1] = scale_vect->cont[1][0];
	scale_mt->cont[2][2] = scale_vect->cont[2][0];
	if (!(res = mt_mul(mt, scale_mt)))
		return (NULL);
	mt_free(&scale_mt);
	return (res);
}

t_matrix	*mt_translate(t_matrix *mt, t_matrix *trans_vect)
{
	t_matrix	*trans_mt;
	t_matrix	*res;

	if (!(trans_vect->h == 3 && trans_vect->w == 1
	&& mt->w == 4 && mt->h == 4))
	{
		if (mt->w != 4 || mt->h != 4)
			fprintf(stderr, "mt need to be a 4x4 matrix");
		else
			fprintf(stderr, "trans_vect need to be a 3x1 matrix");
		return (NULL);
	}
	if (!(trans_mt = mt_new(mt->h, mt->w, TRUE)))
		return (NULL);
	trans_mt->cont[0][3] = trans_vect->cont[0][0];
	trans_mt->cont[1][3] = trans_vect->cont[1][0];
	trans_mt->cont[2][3] = trans_vect->cont[2][0];
	if (!(res = mt_mul(mt, trans_mt)))
		return (NULL);
	mt_free(&trans_mt);
	return (res);
}

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
