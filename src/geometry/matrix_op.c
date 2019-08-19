/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:52:59 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 19:49:41 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	*mt_mul(t_matrix *lhs, t_matrix *rhs)
{
	t_matrix	*res;
	int			i;
	int			j;
	int			k;

	if (lhs->w != rhs->h)
		fprintf(stderr, "to mult matrix lhs wt and rhs ht has to be equal");
	if (lhs->w != rhs->h || !(res = mt_new(rhs->h, rhs->w, FALSE)))
		return (NULL);
	i = -1;
	while (++i < lhs->h)
	{
		j = -1;
		while (++j < rhs->w)
		{
			k = -1;
			while (++k < lhs->w)
			{
				res->cont[i * rhs->w + j] += lhs->cont[i * lhs->w + k] * \
				rhs->cont[k * rhs->w + j];
			}
		}
	}
	return (res);
}

t_matrix	*mt_scale(t_matrix *mt, t_vect3 scale_v)
{
	t_matrix	*scale_mt;
	t_matrix	*res;

	if (!(mt->w == 4 && mt->h == 4))
	{
		fprintf(stderr, "mt need to be a 4x4 matrix");
		return (NULL);
	}
	if (!(scale_mt = mt_new(mt->h, mt->w, TRUE)))
		return (NULL);
	scale_mt->cont[0] = scale_v.x;
	scale_mt->cont[1 * mt->w + 1] = scale_v.y;
	scale_mt->cont[2 * mt->w + 2] = scale_v.z;
	if (!(res = mt_mul(mt, scale_mt)))
		return (NULL);
	mt_free(&scale_mt);
	return (res);
}

t_matrix	*mt_translate(t_matrix *mt, t_vect3 trans_v)
{
	t_matrix	*trans_mt;
	t_matrix	*res;

	if (!(mt->w == 4 && mt->h == 4))
	{
		fprintf(stderr, "mt need to be a 4x4 matrix");
		return (NULL);
	}
	if (!(trans_mt = mt_new(mt->h, mt->w, TRUE)))
		return (NULL);
	trans_mt->cont[3] = trans_v.x;
	trans_mt->cont[1 * mt->w + 3] = trans_v.y;
	trans_mt->cont[2 * mt->w + 3] = trans_v.z;
	if (!(res = mt_mul(mt, trans_mt)))
		return (NULL);
	mt_free(&trans_mt);
	return (res);
}

void		mt_rotate_transform(t_matrix *mt, float angle
, t_vect3 axis_v)
{
	double		cos_angle;
	double		sin_angle;
	float		x;
	float		y;
	float		z;

	x = axis_v.x;
	y = axis_v.y;
	z = axis_v.z;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	mt->cont[0] = cos_angle + (x * x) * (1 - cos_angle);
	mt->cont[1] = x * y * (1 - cos_angle) - z * sin_angle;
	mt->cont[2] = x * z * (1 - cos_angle) + y * sin_angle;
	mt->cont[1 * mt->w] = y * x * (1 - cos_angle) + z * sin_angle;
	mt->cont[1 * mt->w + 1] = cos_angle + (y * y) * (1 - cos_angle);
	mt->cont[1 * mt->w + 2] = y * z * (1 - cos_angle) - x * sin_angle;
	mt->cont[2 * mt->w] = z * x * (1 - cos_angle) - y * sin_angle;
	mt->cont[2 * mt->w + 1] = z * y * (1 - cos_angle) + x * sin_angle;
	mt->cont[2 * mt->w + 2] = cos_angle + (z * z) * (1 - cos_angle);
}

t_matrix	*mt_rotate(t_matrix *mt, float angle, t_vect3 axis_v)
{
	t_matrix	*trans_mt;
	t_matrix	*res;

	if (!(mt->w == 4 && mt->h == 4))
	{
		fprintf(stderr, "mt need to be a 4x4 matrix");
		return (NULL);
	}
	if (!(trans_mt = mt_new(mt->h, mt->w, TRUE)))
		return (NULL);
	mt_rotate_transform(trans_mt, angle, v3_normalize(axis_v));
	if (!(res = mt_mul(mt, trans_mt)))
		return (NULL);
	mt_free(&trans_mt);
	return (res);
}
