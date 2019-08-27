/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:48 by emarin            #+#    #+#             */
/*   Updated: 2019/08/27 15:39:43 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	reg_tk(t_token ***res, const char *word, int nb_reg)
{
	regex_t	regex[nb_reg];
	int		reti;
	char	msgbuf[100];
	int		i;

	(void)reti;
	(void)msgbuf;
	(void)word;
	(void)res;

	printf("word: \"%s\"\n", word);

	i = -1;
	while (++i < nb_reg)
		if (regcomp(regex + i, g_token_reg[i].data, REG_EXTENDED))
		{
			fprintf(stderr, "Could not compile: %s\n", g_token_reg[i].data);
			while (--i >= 0)
				regfree(regex + i);
			return (FALSE);
		}

	i = -1;
	while (++i < nb_reg)
	{
		reti = regexec(regex + i, word, 0, NULL, 0);
		if (!reti)
		{
			printf("Match\n");
		}
		else if (reti == REG_NOMATCH)
		{
			printf("Not match\n");
		}
		else
		{
			regerror(reti, regex, msgbuf, sizeof(msgbuf));
			fprintf(stderr, "Regex match failed: %s\n", msgbuf);
			exit(1);
		}
	}
	printf("_________________\n");

	i = -1;
	while (++i < nb_reg)
		regfree(regex + i);

	return (TRUE);
}

int8_t	fill_tokens(char *line, t_token ***res)
{
	int		s;
	int		e;
	char	word_end;

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
	return (TRUE);
}

int8_t	lexer(const char *filename)
{
	FILE	*fp;
	char	*line;
	size_t	len;
	t_token	**res;

	(void)res;

	if (!(fp = fopen(filename, "r")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (FALSE);
	}

	line = NULL;
	len = 0;
	while (getline(&line, &len, fp) != -1)
	{
		if (!(fill_tokens(line, &res)))
		{
			fclose(fp);
			free(line);
			return (FALSE);
		}
	}

	fclose(fp);
	free(line);
	return (TRUE);
}
