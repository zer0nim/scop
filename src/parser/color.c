/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:38:54 by emarin            #+#    #+#             */
/*   Updated: 2019/09/23 13:40:10 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	register_color(t_obj *obj, int grayscale)
{
	int	start_id;
	int	i;

	i = 4;
	while (--i)
	{
		start_id = (obj->verts_nb_item - i) * V_STEP;
		obj->verts[start_id + 8] = grayscale;
		obj->verts[start_id + 9] = grayscale;
		obj->verts[start_id + 10] = grayscale;
	}
}
