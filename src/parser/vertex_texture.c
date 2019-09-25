/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:57:27 by emarin            #+#    #+#             */
/*   Updated: 2019/09/25 11:58:08 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** rotate vextex by 90 before vt calculation
*/

void	set_vt(t_vertex *v)
{
	t_matrix	*p;
	t_matrix	*mt_id;
	t_matrix	*rot;
	t_matrix	*res;

	p = vect4_m(v->p.x, v->p.y, v->p.z, 1.0f);
\
	mt_id = mt_new(4, 4, TRUE);
	rot = mt_rotate(mt_id, radians(-90.0f), vect3(0.0f, 1.0f, 0.0f));
	res = mt_mul(rot, p);
\
	v->t.x = res->cont[0];
	v->t.y = res->cont[1];
\
	mt_free(&res);
	mt_free(&rot);
	mt_free(&mt_id);
	mt_free(&p);
}
