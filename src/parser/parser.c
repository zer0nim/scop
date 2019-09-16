/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:54 by emarin            #+#    #+#             */
/*   Updated: 2019/09/16 15:37:49 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	parser(t_token_l *lst, int res_size, t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < res_size && lst[i].type != e_empty_t)
		if (g_token_func[lst[i].type].func \
		&& !(g_token_func[lst[i].type].func(lst + i, obj)))
			return (FALSE);
	return (TRUE);
}

int8_t	init_obj(t_obj *obj)
{
	obj->v_max_size = 16;
	if (!(obj->v = (t_vect3 *)malloc(sizeof(t_vect3) * obj->v_max_size)))
		return (FALSE);
	obj->v_nb_item = 0;
	obj->vt_max_size = 16;
	if (!(obj->vt = (t_vect2 *)malloc(sizeof(t_vect2) * obj->vt_max_size)))
		return (FALSE);
	obj->vt_nb_item = 0;
	obj->vn_max_size = 16;
	if (!(obj->vn = (t_vect3 *)malloc(sizeof(t_vect3) * obj->vn_max_size)))
		return (FALSE);
	obj->vn_nb_item = 0;
	obj->verts_max_size = 16;
	if (!(obj->verts = (float *)malloc(sizeof(float) * \
	obj->verts_max_size * V_STEP)))
		return (FALSE);
	obj->verts_nb_item = 0;
	return (TRUE);
}

int8_t	parse_obj(const char *filename)
{
	t_token_l	*lst;
	t_obj		obj;
	int			res_size;

	res_size = 32;
	lst = NULL;
	if (!lexer(filename, &lst, &res_size))
		return (FALSE);
	if (!init_obj(&obj))
		return (FALSE);
	if (!(parser(lst, res_size, &obj)))
	{
		free(obj.v);
		free(obj.vt);
		free(obj.vn);
		free(obj.verts);
		return (FALSE);
	}
	printf("nb_items: %d, max_items: %d\n", obj.verts_nb_item, obj.verts_max_size);
	int	i;
	i = -1;
	while (++i < obj.verts_nb_item)
	{
		printf("{ %f, %f, %f,  %f, %f, %f,  %f, %f }\n", \
		obj.verts[i * V_STEP],
		obj.verts[i * V_STEP + 1],
		obj.verts[i * V_STEP + 2],
		obj.verts[i * V_STEP + 3],
		obj.verts[i * V_STEP + 4],
		obj.verts[i * V_STEP + 5],
		obj.verts[i * V_STEP + 6],
		obj.verts[i * V_STEP + 7]);
	}

	free(obj.v);
	free(obj.vt);
	free(obj.vn);
	free(obj.verts);
	free_token_list(&lst, res_size);
	return (TRUE);
}
