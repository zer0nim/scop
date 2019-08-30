/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:12:37 by emarin            #+#    #+#             */
/*   Updated: 2019/08/30 12:31:54 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	check_grammar(t_token_l *lst)
{
	t_token_func	f_infos;
	t_token_l		*crnt;
	int				count;

	f_infos = g_token_func[lst->type];
	count = 0;
	crnt = lst->next;
	while (crnt && crnt->type == f_infos.arg_type && ++count)
		crnt = crnt->next;
	if (crnt && crnt->type != f_infos.arg_type && crnt->type != e_comments_t)
	{
		fprintf(stderr, "instr %s, bad argument type\n", \
		g_token_reg[lst->type].name);
		return (FALSE);
	}
	if (count < f_infos.min || (!f_infos.accept_more && count > f_infos.min))
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
	printf("vert\n");
	(void)obj;
	if (!(check_grammar(lst)))
		return (FALSE);
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
	(void)obj;
	if (!(check_grammar(lst)))
		return (FALSE);
	return (TRUE);
}

int8_t	parse_text_vert(t_token_l *lst, t_obj *obj)
{
	printf("text_vert\n");
	(void)obj;
	if (!(check_grammar(lst)))
		return (FALSE);
	return (TRUE);
}

int8_t	parse_norm_vert(t_token_l *lst, t_obj *obj)
{
	printf("norm_vert\n");
	(void)obj;
	if (!(check_grammar(lst)))
		return (FALSE);
	return (TRUE);
}
