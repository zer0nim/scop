/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/08/29 18:30:37 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	parse_usemtl(t_token_l *lst, t_obj *obj)
{
	printf("usemtl\n");
	(void)lst;
	(void)obj;
	return (TRUE);
}

int8_t	parse_mtllib(t_token_l *lst, t_obj *obj)
{
	printf("mtllib\n");
	(void)lst;
	(void)obj;
	return (TRUE);
}
