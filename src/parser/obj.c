/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 15:47:21 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 16:54:04 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_obj(t_obj *obj)
{
	free(obj->v);
	free(obj->vt);
	free(obj->vn);
	free(obj->verts);
}

/*
** id start at 1 not 0
*/

int8_t	fill_vertex(t_obj *obj, t_vertex *v, int id, t_vert_type v_type)
{
	int	nb_item;

	if (id != 0)
	{
		if (v_type == e_vp)
			nb_item = obj->v_nb_item;
		if (v_type == e_vn)
			nb_item = obj->vn_nb_item;
		if (v_type == e_vt)
			nb_item = obj->vt_nb_item;
\
		if (id - 1 >= nb_item || id < 0)
		{
			fprintf(stderr, "invalid face index\n");
			return (FALSE);
		}
\
		if (v_type == e_vp)
			v->p = obj->v[id - 1];
		if (v_type == e_vn)
			v->n = obj->vn[id - 1];
		if (v_type == e_vt)
			v->t = obj->vt[id - 1];
	}
	return (TRUE);
}

void	init_v(t_vertex *v)
{
	v->p.x = 0;
	v->p.y = 0;
	v->p.z = 0;
\
	v->n.x = FLT_MAX;
	v->n.y = FLT_MAX;
	v->n.z = FLT_MAX;
\
	v->t.x = FLT_MAX;
	v->t.y = FLT_MAX;
}

/*
** obj->verts:
** positions(vect3),  normals(vect3),  texture_coord(vect2)
** 10, 5, 8,		  1, 0, 0,		   0.5, 0.8, ...
*/

int8_t	fill_obj_verts(t_obj *obj, t_vertex *v)
{
	int	start_id;

	++(obj->verts_nb_item);
	if (obj->verts_nb_item > obj->verts_max_size)
	{
		obj->verts_max_size *= 2;
		if (!(obj->verts = (float *)realloc(obj->verts, sizeof(float) * \
		obj->verts_max_size * V_STEP)))
			return (FALSE);
	}
	start_id = (obj->verts_nb_item - 1) * V_STEP;
	obj->verts[start_id] = v->p.x;
	obj->verts[start_id + 1] = v->p.y;
	obj->verts[start_id + 2] = v->p.z;
\
	obj->verts[start_id + 3] = v->n.x;
	obj->verts[start_id + 4] = v->n.y;
	obj->verts[start_id + 5] = v->n.z;
\
	obj->verts[start_id + 6] = v->t.x;
	obj->verts[start_id + 7] = v->t.y;
	return (TRUE);
}
