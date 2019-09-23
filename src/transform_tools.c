/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:49:12 by emarin            #+#    #+#             */
/*   Updated: 2019/09/19 14:52:43 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_transform	transform(t_vect3 pos, t_vect3 scale, t_vect3 axis, float angle)
{
	t_transform tr;

	tr.pos = pos;
	tr.scale = scale;
	tr.axis = axis;
	tr.angle = angle;
	return (tr);
}
