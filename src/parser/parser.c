/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:54 by emarin            #+#    #+#             */
/*   Updated: 2019/08/30 12:29:41 by emarin           ###   ########.fr       */
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

int8_t	parse_obj(const char *filename)
{
	t_token_l	*lst;
	t_obj		obj;
	int			res_size;

	res_size = 32;
	lst = NULL;
	if (!lexer(filename, &lst, &res_size))
		return (FALSE);
	if (!(parser(lst, res_size, &obj)))
		return (FALSE);
	free_token_list(&lst, res_size);
	return (TRUE);
}
