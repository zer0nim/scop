/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:48 by emarin            #+#    #+#             */
/*   Updated: 2019/08/28 15:52:41 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int8_t	reg_tk(t_token_l **lst, const char *word, int nb_reg, int *res_size, \
int line_nb)
{
	regex_t		regex[nb_reg];
	int			reti;
	int			t;
	t_token_l	*crnt;

	if (line_nb >= *res_size)
		if (!(realloc_tokens(lst, res_size)))
			return (FALSE);

	// maybe move this part to avoid compiling on each word
	t = -1;
	while (++t < nb_reg)
		if (regcomp(regex + t, g_token_reg[t].regex, REG_EXTENDED | REG_NOSUB))
		{
			fprintf(stderr, "Could not compile: %s\n", g_token_reg[t].regex);
			while (--t >= 0)
				regfree(regex + t);
			return (FALSE);
		}

	t = -1;
	while (++t < nb_reg && (reti = regexec(regex + t, word, 0, NULL, 0)))
		if (reti != REG_NOMATCH)
		{
			fprintf(stderr, "Regex exec failed\n");
			t = -1;
			while (++t < nb_reg)
				regfree(regex + t);
			return (FALSE);
		}

	if (!reti)
	{
		crnt = *lst + line_nb;
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
		if (g_token_reg[t].need_data)
			crnt->data = strdup(word);
	}
	else
		;//printf("No match\n");

	t = -1;
	while (++t < nb_reg)
		regfree(regex + t);

	return (TRUE);
}

int8_t	fill_tokens(char *line, t_token_l **lst, int *res_size)
{
	int			s;
	int			e;
	char		word_end;
	static int	line_nb = 0;

	e = 0;
	while (line[e])
	{
		s = e;
		while (line[s] && (line[s] == ' ' || line[s] == '\t' \
		|| line[s] == '\n'))
			++s;
		e = s;
		while (line[e] && (line[e] != ' ' && line[e] != '\t' \
		&& line[e] != '\n'))
			++e;
		if (s != e)
		{
			word_end = line[e];
			line[e] = '\0';
			if (!(reg_tk(lst, line + s, sizeof(g_token_reg) / sizeof(t_token), \
			res_size, line_nb)))
				return (FALSE);
			line[e] = word_end;
		}
	}
	++line_nb;
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

	(void)crnt;

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

int8_t	lexer(const char *filename)
{
	FILE		*fp;
	char		*line;
	t_token_l	*lst;
	int			res_size;
	size_t		line_len;

	if (!(fp = fopen(filename, "r")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (FALSE);
	}

	res_size = 32;
	if (!(lst = (t_token_l *)malloc(sizeof(t_token_l) * res_size)))
		return (FALSE);
	init_token_l(lst, res_size);

	line_len = 0;
	line = NULL;
	while (getline(&line, &line_len, fp) != -1)
	{
		if (!(fill_tokens(line, &lst, &res_size)))
		{
			fclose(fp);
			free(line);
			free_token_list(&lst, res_size);
			return (FALSE);
		}
	}

	fclose(fp);
	free(line);
	print_token_list(lst, res_size);
	free_token_list(&lst, res_size);
	return (TRUE);
}
