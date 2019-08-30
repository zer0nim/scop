/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/08/30 15:07:59 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	i = 0;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*(&(v.x) + i) = atof(crnt->data);
		crnt = crnt->next;
		++i;
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

// When you are using a series of triplets, you must be consistent in the
// way you reference the vertex data. For example, it is illegal to give
// vertex normals for some vertices, but not all.
// The following is an example of an illegal statement.
// f 1/1/1 2/2/2 3//3 4//4
int8_t	parse_face(t_token_l *lst, t_obj *obj)
{
	int	count;

	printf("face\n");
	(void)obj;
	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);
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
	i = 0;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*(&(vt.x) + i) = atof(crnt->data);
		crnt = crnt->next;
		++i;
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
	i = 0;
	crnt = lst->next;
	while (crnt && crnt->type != e_comments_t)
	{
		*(&(vn.x) + i) = atof(crnt->data);
		crnt = crnt->next;
		++i;
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
