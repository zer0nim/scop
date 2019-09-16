/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/09/16 11:45:33 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
* When you are using a series of triplets, you must be consistent in the
* way you reference the vertex data. For example, it is illegal to give
* vertex normals for some vertices, but not all.
* The following is an example of an illegal statement.
* f 1/1/1 2/2/2 3//3 4//4
*/
int8_t	check_face_grammar(t_token_l *lst, int *type)
{
	t_token_l	*crnt;
	int			id;
	int			i;
	int8_t		empty;
	int			last_type;

	last_type = -1;
	id = 0;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*type = 0;
		empty = FALSE;
		id = atoi(crnt->data);
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
				id = atoi(crnt->data + i);
				empty = !id;
			}
		}
		if (last_type != -1 && last_type != *type)
		{
			fprintf(stderr, "instr %s, inconsitent vertice declaration\n", \
			g_token_reg[lst->type].name);
			return (FALSE);
		}
		last_type = *type;
		crnt = crnt->next;
	}
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

/*
* f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
*
* id start at 1 not 0
*
* v_id + '/' + vt_id + '/' + vn_id
*
* 1
* 1/2
* 1/2/3
* 1//3
*
* need to loop through vertices to generate triangles
*
* if there is more than 3 vertices, create the followings triangles:
* 0 1 2, 0 2 3, 0 3 4, ... (like triangle fan)
*
* type 0:	1
* type 1:	1/2
* type 2:	1/2/3
* type 3:	1//3
*
* number of verticies is stored in count
*/
int8_t	parse_face(t_token_l *lst, t_obj *obj)
{
	t_token_l	*crnt;
	int			count;
	int			type;

	printf("face\n");
	(void)obj;
	count = 0;
	type = 0;
	if (!(check_grammar(lst, &count))
	|| !(check_face_grammar(lst, &type)))
		return (FALSE);
	printf("-----------------type: %d\n", type);

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
