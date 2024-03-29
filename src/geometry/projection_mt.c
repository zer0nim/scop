/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_mt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:48:20 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 20:31:24 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_matrix	*mt_perspective(float fov_y, float aspect, float z_near
, float z_far)
{
	t_matrix	*res;
	float		tan_half_fovy;

	if (aspect == 0.0f)
	{
		fprintf(stderr, "perspective aspect can't be set to 0.0\n");
		return (NULL);
	}
	if (z_near == z_far)
	{
		fprintf(stderr, "z_near and z_far are equals\n");
		return (NULL);
	}
	if (!(res = mt_new(4, 4, FALSE)))
		return (NULL);
	tan_half_fovy = tan(fov_y / 2.0f);
	res->cont[0] = 1.0f / (aspect * tan_half_fovy);
	res->cont[1 * 4 + 1] = 1.0f / (tan_half_fovy);
	res->cont[2 * 4 + 2] = -(z_far + z_near) / (z_far - z_near);
	res->cont[2 * 4 + 3] = -(2.0f * z_far * z_near) / (z_far - z_near);
	res->cont[3 * 4 + 2] = -1.0f;
	return (res);
}

t_matrix	*mt_orthographic(t_vect4 l_r_b_t, float z_near, float z_far)
{
	t_matrix	*res;
	float		left;
	float		right;
	float		bottom;
	float		top;

	if (z_near == z_far)
	{
		fprintf(stderr, "z_near and z_far are equals\n");
		return (NULL);
	}
	left = l_r_b_t.x;
	right = l_r_b_t.y;
	bottom = l_r_b_t.z;
	top = l_r_b_t.w;
	if (!(res = mt_new(4, 4, TRUE)))
		return (NULL);
	res->cont[0] = 2.0f / (right - left);
	res->cont[1 * 4 + 1] = 2.0f / (top - bottom);
	res->cont[2 * 4 + 2] = -2.0f / (z_far - z_near);
	res->cont[0 * 4 + 3] = -(right + left) / (right - left);
	res->cont[1 * 4 + 3] = -(top + bottom) / (top - bottom);
	res->cont[2 * 4 + 3] = -(z_far + z_near) / (z_far - z_near);
	return (res);
}

t_matrix	*mt_look_at(t_vect3 pos, t_vect3 target, t_vect3 up)
{
	t_matrix	*res;
	t_vect3		f;
	t_vect3		r;
	t_vect3		u;

	if (!(res = mt_new(4, 4, TRUE)))
		return (NULL);
	f = v3_normalize(v3_sub(target, pos));
	r = v3_normalize(v3_cross(f, up));
	u = v3_cross(r, f);
	res->cont[0] = r.x;
	res->cont[0 * 4 + 1] = r.y;
	res->cont[0 * 4 + 2] = r.z;
	res->cont[1 * 4 + 0] = u.x;
	res->cont[1 * 4 + 1] = u.y;
	res->cont[1 * 4 + 2] = u.z;
	res->cont[2 * 4 + 0] = -f.x;
	res->cont[2 * 4 + 1] = -f.y;
	res->cont[2 * 4 + 2] = -f.z;
	res->cont[0 * 4 + 3] = -v3_dot(r, pos);
	res->cont[1 * 4 + 3] = -v3_dot(u, pos);
	res->cont[2 * 4 + 3] = v3_dot(f, pos);
	return (res);
}
