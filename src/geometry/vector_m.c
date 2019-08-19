/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:08:03 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 19:49:46 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	*vect2_m(float x, float y)
{
	t_matrix	*res;

	if (!(res = mt_new(2, 1, FALSE)))
		return (NULL);
	res->cont[0] = x;
	res->cont[1] = y;
	return (res);
}

t_matrix	*vect3_m(float x, float y, float z)
{
	t_matrix	*res;

	if (!(res = mt_new(3, 1, FALSE)))
		return (NULL);
	res->cont[0] = x;
	res->cont[1] = y;
	res->cont[2] = z;
	return (res);
}

t_matrix	*vect4_m(float x, float y, float z, float w)
{
	t_matrix	*res;

	if (!(res = mt_new(4, 1, FALSE)))
		return (NULL);
	res->cont[0] = x;
	res->cont[1] = y;
	res->cont[2] = z;
	res->cont[3] = w;
	return (res);
}
