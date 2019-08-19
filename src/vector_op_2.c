/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 14:55:55 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 14:05:16 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"

t_vect3	v3_scal_mul(t_vect3 v3, float sc)
{
	t_vect3	res;

	res.x = v3.x * sc;
	res.y = v3.y * sc;
	res.z = v3.z * sc;
	return (res);
}

t_vect3	v3_scal_add(t_vect3 v3, float sc)
{
	t_vect3	res;

	res.x = v3.x + sc;
	res.y = v3.y + sc;
	res.z = v3.z + sc;
	return (res);
}
