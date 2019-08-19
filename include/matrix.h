/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:09:07 by emarin            #+#    #+#             */
/*   Updated: 2019/08/19 20:03:25 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "define.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_matrix
{
	int		w;
	int		h;
	float	*cont;
}				t_matrix;

typedef struct	s_vect2
{
	float	x;
	float	y;
}				t_vect2;

typedef struct	s_vect3
{
	float	x;
	float	y;
	float	z;
}				t_vect3;

typedef struct	s_vect4
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vect4;

t_matrix		*mt_new(int h, int w, int8_t is_identity);
void			mt_print(t_matrix *mt);
void			mt_free(t_matrix **m);

t_matrix		*mt_mul(t_matrix *lhs, t_matrix *rhs);
t_matrix		*mt_scale(t_matrix *mt, t_vect3 scale_v);
t_matrix		*mt_translate(t_matrix *mt, t_vect3 trans_v);
t_matrix		*mt_rotate(t_matrix *mt, float angle, t_vect3 axis_v);
void			mt_add(t_matrix *mt, float add_v);
void			mt_scalar_prod(t_matrix *mt, float scalar_v);

t_matrix		*mt_perspective(float fov_y, float aspect, float z_near\
, float z_far);
t_matrix		*mt_orthographic(t_vect4 l_r_b_t, float z_near, float z_far);
t_matrix		*mt_look_at(t_vect3 pos, t_vect3 target, t_vect3 up);

t_vect2			vect2(float x, float y);
t_vect3			vect3(float x, float y, float z);
t_vect4			vect4(float x, float y, float z, float w);

t_vect3			v3_normalize(t_vect3 v);
float			v3_dot(t_vect3 lhs, t_vect3 rhs);
t_vect3			v3_cross(t_vect3 lhs, t_vect3 rhs);
t_vect3			v3_add(t_vect3 lhs, t_vect3 rhs);
t_vect3			v3_sub(t_vect3 lhs, t_vect3 rhs);
t_vect3			v3_scal_mul(t_vect3 v3, float sc);
t_vect3			v3_scal_add(t_vect3 v3, float sc);

t_matrix		*vect2_m(float x, float y);
t_matrix		*vect3_m(float x, float y, float z);
t_matrix		*vect4_m(float x, float y, float z, float w);

#endif
