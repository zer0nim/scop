/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:47:48 by emarin            #+#    #+#             */
/*   Updated: 2019/08/26 17:09:27 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int8_t	lexer(const char *filename)
{
	FILE	*fp;
	char	*line;
	size_t	len;

	if (!(fp = fopen(filename, "r")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (FALSE);
	}

	line = NULL;
	len = 0;
	while (getline(&line, &len, fp) != -1)
	{
		printf("%s", line);
	}

	printf("_______________\nMax line size: %zd\n", len);

	fclose(fp);
	free(line);
	return (TRUE);
}
