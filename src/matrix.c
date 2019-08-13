/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:10:50 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 14:06:40 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "matrix.h"

void		mt_free_cont(float ***cont, int h)
{
	int i;

	i = -1;
	while (++i < h)
	{
		if ((*cont)[i])
		{
			free((*cont)[i]);
			(*cont)[i] = NULL;
		}
	}
	free((*cont));
	(*cont) = NULL;
}

void		mt_free(t_matrix **m)
{
	if ((*m)->cont)
		mt_free_cont(&((*m)->cont), (*m)->h);
	if ((*m))
	{
		free((*m));
		(*m) = NULL;
	}
}

float		**mt_new_cont(int h, int w, int8_t is_identity)
{
	float	**cont;
	int		i;
	int		j;

	if (!(cont = (float **)malloc(sizeof(float *) * h)))
		return (NULL);
	i = -1;
	while (++i < h)
	{
		if (!(cont[i] = (float *)malloc(sizeof(float) * w)))
		{
			mt_free_cont(&cont, i);
			return (NULL);
		}
		j = -1;
		while (++j < w)
			cont[i][j] = (is_identity && j == i) ? 1.0 : 0.0;
	}
	return (cont);
}

t_matrix	*mt_new(int h, int w, int8_t is_identity)
{
	t_matrix	*mt;

	if (!(mt = (t_matrix *)malloc(sizeof(t_matrix *))))
		return (NULL);
	mt->w = w;
	mt->h = h;
	if (!(mt->cont = mt_new_cont(h, w, is_identity)))
	{
		free(mt);
		return (NULL);
	}
	return (mt);
}

void		mt_print(t_matrix *mt)
{
	int i;
	int j;

	printf("(\n");
	i = -1;
	while (++i < mt->h)
	{
		j = -1;
		while (++j < mt->w)
			printf("\t%.2f", mt->cont[i][j]);
		printf("\n");
	}
	printf(")\n");
}
