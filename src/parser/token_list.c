/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:14:20 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 15:16:29 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	add_token(t_token_l *crnt, const char *word, int reti, int t)
{
	if (!reti)
	{
		if (crnt->next || crnt->type != e_empty_t)
		{
			while (crnt->next)
				crnt = crnt->next;
			if (!(crnt->next = (t_token_l *)malloc(sizeof(t_token_l))))
				return (FALSE);
			crnt = crnt->next;
		}
		crnt->next = NULL;
		crnt->type = t;
		crnt->data = NULL;
		if (g_token_reg[t].need_data)
			crnt->data = strdup(word);
	}
	else
	{
		fprintf(stderr, "Unrecognized token \"%s\"\n", word);
		return (FALSE);
	}
	return (TRUE);
}

void	init_token_l(t_token_l *lst, int res_size)
{
	int	i;

	i = -1;
	while (++i < res_size)
	{
		lst[i].type = e_empty_t;
		lst[i].data = NULL;
		lst[i].next = NULL;
	}
}

int8_t	realloc_tokens(t_token_l **lst, int *res_size)
{
	t_token_l	*new_res;
	int			old_size;

	old_size = *res_size;
	*res_size *= 2;
	if (!(new_res = (t_token_l *)realloc(*lst, sizeof(t_token_l) * *res_size)))
		return (FALSE);
	*lst = new_res;
	init_token_l(*lst + old_size, old_size);
	return (TRUE);
}

void	free_token_list(t_token_l **lst, int res_size)
{
	t_token_l	*crnt;
	t_token_l	*prev;

	while (--res_size >= 0)
	{
		crnt = *lst + res_size;
		if (crnt->data)
			free(crnt->data);
		if (crnt->next)
		{
			crnt = crnt->next;
			while (crnt)
			{
				prev = crnt;
				crnt = crnt->next;
				if (prev->data)
					free(prev->data);
				free(prev);
			}
		}
	}
	free(*lst);
}

void	print_token_list(t_token_l *lst, int res_size)
{
	t_token_l	*crnt;
	int			i;

	i = 0;
	while (i < res_size && lst[i].type != e_empty_t)
	{
		printf("=================== line %d\n", i);
		crnt = lst + i;
		while (crnt)
		{
			if (crnt != lst + i)
				printf("_______\n");
			printf("type: %s\n", g_token_reg[crnt->type].name);
			printf("data: %s\n", crnt->data);
			crnt = crnt->next;
		}
		++i;
	}
}
