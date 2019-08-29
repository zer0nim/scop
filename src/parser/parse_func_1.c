/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/08/29 19:26:35 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	check_grammar(t_token_l *lst)
{
	(void)lst;
	return (TRUE);
}

int8_t	parse_vert(t_token_l *lst, t_obj *obj)
{
	t_token_l	*crnt;

	printf("vert\n");
	(void)obj;

	crnt = lst;
	if (!(check_grammar(lst)))
		return (FALSE);
	crnt = lst->next;
	while (crnt)
	{
		printf("type: %s\n", g_token_reg[crnt->type].name);
		printf("data: %s\n", crnt->data);
		crnt = crnt->next;
	}
	return (TRUE);
}

// When you are using a series of triplets, you must be consistent in the
// way you reference the vertex data. For example, it is illegal to give
// vertex normals for some vertices, but not all.
// The following is an example of an illegal statement.
// f 1/1/1 2/2/2 3//3 4//4
int8_t	parse_face(t_token_l *lst, t_obj *obj)
{
	printf("face\n");
	(void)lst;
	(void)obj;
	return (TRUE);
}

int8_t	parse_text_vert(t_token_l *lst, t_obj *obj)
{
	printf("text_vert\n");
	(void)lst;
	(void)obj;
	return (TRUE);
}

int8_t	parse_norm_vert(t_token_l *lst, t_obj *obj)
{
	printf("norm_vert\n");
	(void)lst;
	(void)obj;
	return (TRUE);
}
