/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:48 by emarin            #+#    #+#             */
/*   Updated: 2019/08/27 18:55:34 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	reg_tk(t_token_l *res, const char *word, int nb_reg)
{
	regex_t	regex[nb_reg];
	int		reti;
	int		i;

	(void)res;

	i = -1;
	while (++i < nb_reg)
		if (regcomp(regex + i, g_token_reg[i].regex, REG_EXTENDED | REG_NOSUB))
		{
			fprintf(stderr, "Could not compile: %s\n", g_token_reg[i].regex);
			while (--i >= 0)
				regfree(regex + i);
			return (FALSE);
		}

	i = -1;
	while (++i < nb_reg && (reti = regexec(regex + i, word, 0, NULL, 0)))
		if (reti != REG_NOMATCH)
		{
			fprintf(stderr, "Regex exec failed\n");
			i = -1;
			while (++i < nb_reg)
				regfree(regex + i);
			return (FALSE);
		}
	// printf("word: \"%s\"\n", word);
	if (!reti)
		;//printf("Match id %d\n", i);
	else
		;//printf("No match\n");

	i = -1;
	while (++i < nb_reg)
		regfree(regex + i);

	return (TRUE);
}

int8_t	fill_tokens(char *line, t_token_l *res)
{
	int		s;
	int		e;
	char	word_end;
	int		i;

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
			if (!(reg_tk(res, line + s, sizeof(g_token_reg) / sizeof(t_token))))
				return (FALSE);
			line[e] = word_end;
		}
	}

	i = 0;
	while (res[i].type != e_empty_t)
		++i;
	res[i].type = e_comments_t;
	printf("----i = %d\n", i);

	return (TRUE);
}

void	init_token_l(t_token_l *res, int res_size)
{
	int	i;

	i = -1;
	while (++i < res_size)
	{
		res[i].type = e_empty_t;
		res[i].data = NULL;
		res[i].next = NULL;
	}
}

int8_t	realloc_tokens(t_token_l **res, int *res_size)
{
	t_token_l	*new_res;
	int			old_size;

	old_size = *res_size;
	*res_size *= 2;
	if (!(new_res = realloc(*res, sizeof(t_token_l) * *res_size)))
	{
		free(*res);
		// need to free res content !
		return (FALSE);
	}
	*res = new_res;
	init_token_l(*res + old_size, old_size);
	return (TRUE);
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// I Need to move the realloc part because one line can have multiples tokens
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int8_t	lexer(const char *filename)
{
	FILE		*fp;
	char		*line;
	t_token_l	*res;
	int			res_size;
	int			line_nb;
	size_t		line_len;

	if (!(fp = fopen(filename, "r")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (FALSE);
	}

	res_size = 32;
	if (!(res = (t_token_l *)malloc(sizeof(t_token_l) * res_size)))
		return (FALSE);
	init_token_l(res, res_size);

	line_nb = 0;
	line_len = 0;
	line = NULL;
	while (getline(&line, &line_len, fp) != -1)
	{
		printf("line %d\n", line_nb);
		if (line_nb >= res_size)
			if (!(realloc_tokens(&res, &res_size)))
				return (FALSE);
		if (!(fill_tokens(line, res)))
		{
			fclose(fp);
			free(line);
			free(res);
			return (FALSE);
		}
		++line_nb;
	}

	fclose(fp);
	free(line);
	free(res);
	return (TRUE);
}
