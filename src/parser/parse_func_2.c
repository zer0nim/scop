/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 15:18:59 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	parse_usemtl(t_token_l *lst, t_obj *obj)
{
	int	count;

	(void)obj;
	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);
	return (TRUE);
}

int8_t	parse_mtllib(t_token_l *lst, t_obj *obj)
{
	int	count;

	(void)obj;
	count = 0;
	if (!(check_grammar(lst, &count)))
		return (FALSE);
	return (TRUE);
}
