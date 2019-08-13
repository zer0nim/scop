/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:09:07 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 14:04:12 by emarin           ###   ########.fr       */
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
t_matrix	*mt_scale(t_matrix *mt, t_matrix *scale_vect);
t_matrix	*mt_translate(t_matrix *mt, t_matrix *trans_vect);
t_matrix	*mt_rotate(t_matrix *mt, float angle, t_matrix *axis_vect);
void		mt_add(t_matrix *mt, float add_v);
void		mt_scalar_prod(t_matrix *mt, float scalar_v);

t_matrix	*vect2(float x, float y);
t_matrix	*vect3(float x, float y, float z);
t_matrix	*vect4(float x, float y, float z, float w);

#endif
