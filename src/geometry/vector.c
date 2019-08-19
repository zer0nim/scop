/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:03:31 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 19:50:31 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vect2			vect2(float x, float y)
{
	t_vect2	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vect3			vect3(float x, float y, float z)
{
	t_vect3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vect4			vect4(float x, float y, float z, float w)
{
	t_vect4	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}
