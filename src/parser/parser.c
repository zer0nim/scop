/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:54 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 15:22:07 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	normalize_coord(t_obj *obj, t_vect3 min, t_vect3 max)
{
	float		max_diff;
	int			i;

	if ((max.x - min.x) > (max.y - min.y))
		max_diff = ((max.x - min.x) > (max.z - min.z)) ? (max.x - min.x) \
		: (max.z - min.z);
	else
		max_diff = ((max.y - min.y) > (max.z - min.z)) ? (max.y - min.y) \
		: (max.z - min.z);
\
	i = -1;
	while (++i < obj->verts_nb_item)
	{
		obj->verts[i * V_STEP] += -(max.x + min.x) / 2.0f;
		obj->verts[i * V_STEP + 1] += -(max.y + min.y) / 2.0f;
		obj->verts[i * V_STEP + 2] += -(max.z + min.z) / 2.0f;
\
		obj->verts[i * V_STEP] /= max_diff;
		obj->verts[i * V_STEP + 1] /= max_diff;
		obj->verts[i * V_STEP + 2] /= max_diff;
	}
}

void	norm_device_coord(t_obj *obj)
{
	int		i;
	t_vect3	min;
	t_vect3	max;
	int8_t	first_loop;

	first_loop = TRUE;
	i = -1;
	while (++i < obj->verts_nb_item)
	{
		if (first_loop || min.x > obj->verts[i * V_STEP])
			min.x = obj->verts[i * V_STEP];
		if (first_loop || min.y > obj->verts[i * V_STEP + 1])
			min.y = obj->verts[i * V_STEP + 1];
		if (first_loop || min.z > obj->verts[i * V_STEP + 2])
			min.z = obj->verts[i * V_STEP + 2];
		if (first_loop || max.x < obj->verts[i * V_STEP])
			max.x = obj->verts[i * V_STEP];
		if (first_loop || max.y < obj->verts[i * V_STEP + 1])
			max.y = obj->verts[i * V_STEP + 1];
		if (first_loop || max.z < obj->verts[i * V_STEP + 2])
			max.z = obj->verts[i * V_STEP + 2];
		first_loop = FALSE;
	}
	normalize_coord(obj, min, max);
}

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

int8_t	parse_obj(const char *filename, t_obj *obj)
{
	t_token_l	*lst;
	int			res_size;

	res_size = 32;
	lst = NULL;
	if (!lexer(filename, &lst, &res_size))
		return (FALSE);
	if (!init_obj(obj))
		return (FALSE);
	if (!(parser(lst, res_size, obj)))
	{
		free_obj(obj);
		return (FALSE);
	}
	norm_device_coord(obj);
	free_token_list(&lst, res_size);
	return (TRUE);
}
