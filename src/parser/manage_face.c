/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_face.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:55:33 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 16:56:34 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_type(int *type, t_token_l *crnt)
{
	int		i;
	int8_t	empty;

	empty = FALSE;
	i = 0;
	while (crnt->data[i])
	{
		while (crnt->data[i] && crnt->data[i] != '/')
			++i;
		if (crnt->data[i] == '/')
		{
			++i;
			++(*type);
			if (*type == 2 && empty)
				*type = 3;
			empty = !atoi(crnt->data + i);
		}
	}
}

/*
** Check for consistency when declaring face indexes.
** For example, it is illegal to give vertex normals for only some vertices.
** like: "f 1/1/1 2/2/2 3//3 4//4"
*/

int8_t	check_face_grammar(t_token_l *lst, t_obj *obj)
{
	t_token_l	*crnt;
	int			last_type;

	last_type = -1;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		obj->f_type = 0;
		check_type(&(obj->f_type), crnt);
		if (last_type != -1 && last_type != obj->f_type)
		{
			fprintf(stderr, "instr %s, inconsitent vertice declaration\n", \
			g_token_reg[lst->type].name);
			return (FALSE);
		}
		last_type = obj->f_type;
		crnt = crnt->next;
	}
	return (TRUE);
}

t_vect3	calc_face_norm(t_vect3 p1, t_vect3 p2, t_vect3 p3)
{
	t_vect3	u;
	t_vect3	v;

	u = v3_sub(p2, p1);
	v = v3_sub(p3, p1);
	return (v3_normalize(v3_cross(u, v)));
}

/*
** type 0:	1
** type 1:	1/2
** type 2:	1/2/3
** type 3:	1//3
*/

int8_t	add_vt(t_obj *obj, char *v_str)
{
	char		*pos;
	t_vertex	v;

	init_v(&v);
	if (!(fill_vertex(obj, &v, atof(v_str), e_vp)))
		return (FALSE);
	if (obj->f_type >= 1)
	{
		if (!(pos = strchr(v_str, '/')))
			return (FALSE);
		if (!(fill_vertex(obj, &v, atof(pos + 1), e_vt)))
			return (FALSE);
	}
	v.t.x = v.p.x;
	v.t.y = v.p.y;
	if (obj->f_type >= 2)
	{
		if (!(pos = strchr(pos + 1, '/')))
			return (FALSE);
		if (!(fill_vertex(obj, &v, atof(pos + 1), e_vn)))
			return (FALSE);
	}
	if (!(fill_obj_verts(obj, &v)))
		return (FALSE);
	return (TRUE);
}

int8_t	register_triangle(t_obj *obj, t_token_l *a, t_token_l *b, t_token_l *c)
{
	int		start_id;
	t_vect3	n;

	if (!(add_vt(obj, a->data)) || !(add_vt(obj, b->data)) || \
	!(add_vt(obj, c->data)))
		return (FALSE);
	start_id = (obj->verts_nb_item - 3) * V_STEP;
	if (obj->verts[start_id + 3] == FLT_MAX)
	{
		n = calc_face_norm(*((t_vect3 *)(obj->verts + start_id)), \
		*((t_vect3 *)(obj->verts + ((obj->verts_nb_item - 2) * V_STEP))), \
		*((t_vect3 *)(obj->verts + ((obj->verts_nb_item - 1) * V_STEP))));
		obj->verts[start_id + 3] = n.x;
		obj->verts[start_id + 4] = n.y;
		obj->verts[start_id + 5] = n.z;
		start_id = (obj->verts_nb_item - 2) * V_STEP;
		obj->verts[start_id + 3] = n.x;
		obj->verts[start_id + 4] = n.y;
		obj->verts[start_id + 5] = n.z;
		start_id = (obj->verts_nb_item - 1) * V_STEP;
		obj->verts[start_id + 3] = n.x;
		obj->verts[start_id + 4] = n.y;
		obj->verts[start_id + 5] = n.z;
	}
	return (TRUE);
}
