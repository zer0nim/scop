/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:48 by emarin            #+#    #+#             */
/*   Updated: 2019/08/28 19:23:14 by emarin           ###   ########.fr       */
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

int8_t	reg_tk(t_token_l **lst, const char *word, int *res_size, \
regex_t *regex, int line_nb)
{
	int			reti;
	int			t;
	int			nb_reg;

	if (line_nb >= *res_size)
		if (!(realloc_tokens(lst, res_size)))
			return (FALSE);
	nb_reg = sizeof(g_token_reg) / sizeof(t_token);
	t = -1;
	while (++t < nb_reg && (reti = regexec(regex + t, word, 0, NULL, 0)))
		if (reti != REG_NOMATCH)
		{
			fprintf(stderr, "Regex exec failed\n");
			return (FALSE);
		}
	if (!(add_token(*lst + line_nb, word, reti, t)))
		return (FALSE);
	return (TRUE);
}

int8_t	fill_tokens(char *line, t_token_l **lst, int *res_size, regex_t *regex)
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
			if (!(reg_tk(lst, line + s, res_size, regex, line_nb)))
				return (FALSE);
			line[e] = word_end;
		}
	}
	++line_nb;
	return (TRUE);
}

int8_t	lexer_loop(FILE *fp, t_token_l **lst, int *res_size)
{
	char		*line;
	size_t		line_len;
	regex_t		regex[sizeof(g_token_reg) / sizeof(t_token)];

	if (!(compile_reg(regex, sizeof(g_token_reg) / sizeof(t_token))))
		return (FALSE);
	line_len = 0;
	line = NULL;
	while (getline(&line, &line_len, fp) != -1)
	{
		if (!(fill_tokens(line, lst, res_size, regex)))
		{
			free(line);
			free_token_list(lst, *res_size);
			free_reg(regex, sizeof(g_token_reg) / sizeof(t_token));
			return (FALSE);
		}
	}
	free(line);
	free_reg(regex, sizeof(g_token_reg) / sizeof(t_token));
	return (TRUE);
}

int8_t	lexer(const char *filename, t_token_l **lst, int *res_size)
{
	FILE		*fp;

	if (!(fp = fopen(filename, "r")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (FALSE);
	}
	if (!(*lst = (t_token_l *)malloc(sizeof(t_token_l) * *res_size)))
		return (FALSE);
	init_token_l(*lst, *res_size);
	if (!(lexer_loop(fp, lst, res_size)))
	{
		fclose(fp);
		return (FALSE);
	}
	fclose(fp);
	return (TRUE);
}
