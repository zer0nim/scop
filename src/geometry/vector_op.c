/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 14:55:55 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 20:31:24 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vect3	v3_normalize(t_vect3 v)
{
	float	len;
	float	sqrt_len;

	len = v.x * v.x + v.y * v.y + v.z * v.z;
	if (len > 0)
	{
		sqrt_len = sqrt(len);
		v.x /= sqrt_len;
		v.y /= sqrt_len;
		v.z /= sqrt_len;
	}
	return (v);
}

float	v3_dot(t_vect3 lhs, t_vect3 rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

t_vect3	v3_cross(t_vect3 lhs, t_vect3 rhs)
{
	t_vect3	res;

	res.x = lhs.y * rhs.z - lhs.z * rhs.y;
	res.y = lhs.z * rhs.x - lhs.x * rhs.z;
	res.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return (res);
}

t_vect3	v3_add(t_vect3 lhs, t_vect3 rhs)
{
	t_vect3	res;

	res.x = lhs.x + rhs.x;
	res.y = lhs.y + rhs.y;
	res.z = lhs.z + rhs.z;
	return (res);
}

t_vect3	v3_sub(t_vect3 lhs, t_vect3 rhs)
{
	t_vect3	res;

	res.x = lhs.x - rhs.x;
	res.y = lhs.y - rhs.y;
	res.z = lhs.z - rhs.z;
	return (res);
}
