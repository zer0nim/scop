/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:54 by emarin            #+#    #+#             */
/*   Updated: 2019/08/30 15:35:03 by emarin           ###   ########.fr       */
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
		return (FALSE);
	}
	free(obj.v);
	free(obj.vt);
	free(obj.vn);
	free_token_list(&lst, res_size);
	return (TRUE);
}
