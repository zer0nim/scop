/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:52:59 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 14:36:14 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"
#include <math.h>

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

void		mt_rotate_transform(t_matrix *trans_mt, float angle
, t_matrix *axis_vect)
{
	double		cos_angle;
	double		sin_angle;
	float		x;
	float		y;
	float		z;

	x = axis_vect->cont[0][0];
	y = axis_vect->cont[1][0];
	z = axis_vect->cont[2][0];
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	trans_mt->cont[0][0] = cos_angle + (x * x) * (1 - cos_angle);
	trans_mt->cont[0][1] = x * y * (1 - cos_angle) - z * sin_angle;
	trans_mt->cont[0][2] = x * z * (1 - cos_angle) + y * sin_angle;
	trans_mt->cont[1][0] = y * x * (1 - cos_angle) + z * sin_angle;
	trans_mt->cont[1][1] = cos_angle + (y * y) * (1 - cos_angle);
	trans_mt->cont[1][2] = y * z * (1 - cos_angle) - x * sin_angle;
	trans_mt->cont[2][0] = z * x * (1 - cos_angle) - y * sin_angle;
	trans_mt->cont[2][1] = z * y * (1 - cos_angle) + x * sin_angle;
	trans_mt->cont[2][2] = cos_angle + (z * z) * (1 - cos_angle);
}

t_matrix	*mt_rotate(t_matrix *mt, float angle, t_matrix *axis_vect)
{
	t_matrix	*trans_mt;
	t_matrix	*res;

	if (!(axis_vect->h == 3 && axis_vect->w == 1
	&& mt->w == 4 && mt->h == 4))
	{
		if (mt->w != 4 || mt->h != 4)
			fprintf(stderr, "mt need to be a 4x4 matrix");
		else
			fprintf(stderr, "axis_vect need to be a 3x1 matrix");
		return (NULL);
	}
	if (!(trans_mt = mt_new(mt->h, mt->w, TRUE)))
		return (NULL);
	mt_rotate_transform(trans_mt, angle, axis_vect);
	if (!(res = mt_mul(mt, trans_mt)))
		return (NULL);
	mt_free(&trans_mt);
	return (res);
}
