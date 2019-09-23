/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:12:43 by emarin            #+#    #+#             */
/*   Updated: 2019/08/28 19:12:53 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_reg(regex_t *regex, int nb_reg)
{
	int	t;

	t = -1;
	while (++t < nb_reg)
		regfree(regex + t);
}

int8_t	compile_reg(regex_t *regex, int nb_reg)
{
	int			t;

	t = -1;
	while (++t < nb_reg)
		if (regcomp(regex + t, g_token_reg[t].regex, REG_EXTENDED | REG_NOSUB))
		{
			fprintf(stderr, "Could not compile: %s\n", g_token_reg[t].regex);
			while (--t >= 0)
				regfree(regex + t);
			return (FALSE);
		}
	return (TRUE);
}
