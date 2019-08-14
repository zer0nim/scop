/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:03:31 by emarin            #+#    #+#             */
/*   Updated: 2019/08/14 15:58:58 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"

t_matrix	*vect2_m(float x, float y)
{
	t_matrix	*res;

	if (!(res = mt_new(2, 1, FALSE)))
		return (NULL);
	res->cont[0][0] = x;
	res->cont[1][0] = y;
	return (res);
}

t_matrix	*vect3_m(float x, float y, float z)
{
	t_matrix	*res;

	if (!(res = mt_new(3, 1, FALSE)))
		return (NULL);
	res->cont[0][0] = x;
	res->cont[1][0] = y;
	res->cont[2][0] = z;
	return (res);
}

t_matrix	*vect4_m(float x, float y, float z, float w)
{
	t_matrix	*res;

	if (!(res = mt_new(4, 1, FALSE)))
		return (NULL);
	res->cont[0][0] = x;
	res->cont[1][0] = y;
	res->cont[2][0] = z;
	res->cont[3][0] = w;
	return (res);
}

t_vect2			vect2(float x, float y) {
	t_vect2	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vect3			vect3(float x, float y, float z) {
	t_vect3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}
