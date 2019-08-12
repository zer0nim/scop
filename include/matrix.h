/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:09:07 by emarin            #+#    #+#             */
/*   Updated: 2019/08/12 17:37:21 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "scop.h"

typedef struct		s_matrix
{
	int		w;
	int		h;
	float	**cont;
}					t_matrix;

t_matrix	*mt_new(int h, int w, int8_t is_identity);
void		mt_print(t_matrix *mt);
void		mt_free(t_matrix **m);

t_matrix	*mt_mul(t_matrix *lhs, t_matrix *rhs);

#endif
