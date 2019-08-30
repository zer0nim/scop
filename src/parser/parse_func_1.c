/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/08/30 16:29:37 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// When you are using a series of triplets, you must be consistent in the
// way you reference the vertex data. For example, it is illegal to give
// vertex normals for some vertices, but not all.
// The following is an example of an illegal statement.
// f 1/1/1 2/2/2 3//3 4//4
//
// type 0:	1
// type 1:	1/2
// type 2:	1/2/3
// type 3:	1//3
int8_t	check_face_grammar(t_token_l *lst)
{
	t_token_l	*crnt;
	int			id;
	int			i;
	int			type;

	printf("check_face_grammar\n");
	id = 0;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		type = 0;
		printf("crnt->data: \"%s\"\n", crnt->data);
		id = atoi(crnt->data);
		printf("id's: {%d", id);

		i = 0;
		while (crnt->data[i])
		{
			while (crnt->data[i] && crnt->data[i] != '/')
				++i;
			if (crnt->data[i] == '/')
			{
				++i;
				++type;
				id = atoi(crnt->data + i);
				printf(", %d", id);
			}
		}
		printf("} type: %d\n", type);

		printf("__\n");
		crnt = crnt->next;
	}
	printf("___________\n");

	// if ()
	// {
	// 	fprintf(stderr, "instr %s, inconsitent vertice declaration\n", \
	// 	g_token_reg[lst->type].name);
	// 	return (FALSE);
	// }

	// check indices here or in parse_face ?
	return (TRUE);
}

int8_t	check_grammar(t_token_l *lst, int *count)
{
	t_token_func	f_infos;
	t_token_l		*crnt;

	f_infos = g_token_func[lst->type];
	*count = 0;
	crnt = lst->next;
	while (crnt && crnt->type == f_infos.arg_type && ++(*count))
		crnt = crnt->next;
	if (crnt && crnt->type != f_infos.arg_type && crnt->type != e_comments_t)
	{
		fprintf(stderr, "instr %s, bad argument type\n", \
		g_token_reg[lst->type].name);
		return (FALSE);
	}
	if (*count < f_infos.min || (!f_infos.accept_more && *count > f_infos.min))
	{
		fprintf(stderr, "instr %s need %d%sarguments\n", \
		g_token_reg[lst->type].name, f_infos.min, \
		(f_infos.accept_more ? "or more " : ""));
		return (FALSE);
	}
	if (lst->type == e_face_t)
		return (check_face_grammar(lst));
	return (TRUE);
}

int8_t	parse_vert(t_token_l *lst, t_obj *obj)
{
	t_token_l		*crnt;
	t_vect3			v;
	int				count;
	int				i;

	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);
	i = -1;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*(&(v.x) + ++i) = atof(crnt->data);
		crnt = crnt->next;
	}
	++(obj->v_nb_item);
	if (obj->v_nb_item > obj->v_max_size)
	{
		obj->v_max_size *= 2;
		if (!(obj->v = (t_vect3 *)realloc(obj->v, sizeof(t_vect3) * \
		obj->v_max_size)))
			return (FALSE);
	}
	obj->v[obj->v_nb_item - 1] = v;
	return (TRUE);
}

// f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
//
// id start at 1 not 0
//
// v_id + '/' + vt_id + '/' + vn_id
//
// 1
// 1/2
// 1/2/3
// 1//3
//
// need to loop through vertices to generate triangles
//
// if there is more than 3 vertices, create the followings triangles:
// 0 1 2, 0 2 3, 0 3 4, ... (like triangle fan)
int8_t	parse_face(t_token_l *lst, t_obj *obj)
{
	t_token_l	*crnt;
	int			count;

	printf("face\n");
	(void)obj;
	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);

	// number of verticies is stored in count
	// need to know the number of args per verticies (0 || 1 || 2) ?
	// -> just count the number of '/'

	// in progress
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		printf("crnt->data: \"%s\"\n", crnt->data);
		crnt = crnt->next;
	}
	printf("___________\n");
	return (TRUE);
}

int8_t	parse_text_vert(t_token_l *lst, t_obj *obj)
{
	t_token_l		*crnt;
	t_vect2			vt;
	int				count;
	int				i;

	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);
	i = -1;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*(&(vt.x) + ++i) = atof(crnt->data);
		crnt = crnt->next;
	}
	++(obj->vt_nb_item);
	if (obj->vt_nb_item > obj->vt_max_size)
	{
		obj->vt_max_size *= 2;
		if (!(obj->vt = (t_vect2 *)realloc(obj->vt, sizeof(t_vect2) * \
		obj->vt_max_size)))
			return (FALSE);
	}
	obj->vt[obj->vt_nb_item - 1] = vt;
	return (TRUE);
}

int8_t	parse_norm_vert(t_token_l *lst, t_obj *obj)
{
	t_token_l		*crnt;
	t_vect3			vn;
	int				count;
	int				i;

	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);
	i = -1;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*(&(vn.x) + ++i) = atof(crnt->data);
		crnt = crnt->next;
	}
	++(obj->vn_nb_item);
	if (obj->vn_nb_item > obj->vn_max_size)
	{
		obj->vn_max_size *= 2;
		if (!(obj->vn = (t_vect3 *)realloc(obj->vn, sizeof(t_vect3) * \
		obj->vn_max_size)))
			return (FALSE);
	}
	obj->vn[obj->vn_nb_item - 1] = vn;
	return (TRUE);
}
