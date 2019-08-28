/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:54 by emarin            #+#    #+#             */
/*   Updated: 2019/08/28 16:10:11 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	parser(void)
{
	return (TRUE);
}

int8_t	parse_obj(const char *filename)
{
	t_token_l	*lst;
	int			res_size;

	res_size = 32;
	lst = NULL;
	if (!lexer(filename, &lst, &res_size))
		return (FALSE);
	print_token_list(lst, res_size);
	free_token_list(&lst, res_size);
	return (TRUE);
}
