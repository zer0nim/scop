/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:48 by emarin            #+#    #+#             */
/*   Updated: 2019/09/18 15:16:25 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	reg_tk(t_token_l **lst, const char *word, regex_t *regex, int line_nb)
{
	int			reti;
	int			t;
	int			nb_reg;

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

void	next_word(char *line, int *s, int *e)
{
	*s = *e;
	while (line[*s] && (line[*s] == ' ' || line[*s] == '\t' \
	|| line[*s] == '\n'))
		++(*s);
	*e = (line[*s] != '#') ? *s : strlen(line);
	while (line[*e] && (line[*e] != ' ' && line[*e] != '\t' \
	&& line[*e] != '\n' && line[*e] != '#'))
		++(*e);
}

int8_t	fill_tokens(char *line, t_token_l **lst, int line_nb, regex_t *regex)
{
	int			s;
	int			e;
	char		word_end;
	int8_t		empty;

	empty = TRUE;
	e = 0;
	while (line[e])
	{
		next_word(line, &s, &e);
		if (s != e)
		{
			empty = FALSE;
			word_end = line[e];
			line[e] = '\0';
			if (!(reg_tk(lst, line + s, regex, line_nb)))
				return (FALSE);
			line[e] = word_end;
		}
	}
	if (empty && !(add_token(*lst + line_nb, NULL, FALSE, e_comments_t)))
		return (FALSE);
	return (TRUE);
}

int8_t	lexer_loop(FILE *fp, t_token_l **lst, int *res_size)
{
	char		*line;
	size_t		line_len;
	regex_t		regex[sizeof(g_token_reg) / sizeof(t_token)];
	static int	line_nb = -1;

	if (!(compile_reg(regex, sizeof(g_token_reg) / sizeof(t_token))))
		return (FALSE);
	line_len = 0;
	line = NULL;
	while (getline(&line, &line_len, fp) != -1)
	{
		++line_nb;
		if (line_nb >= *res_size && !(realloc_tokens(lst, res_size)))
			return (FALSE);
		if (!(fill_tokens(line, lst, line_nb, regex)))
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
