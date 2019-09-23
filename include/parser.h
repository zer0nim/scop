/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:49:38 by emarin            #+#    #+#             */
/*   Updated: 2019/09/23 12:08:10 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "geometry.h"
# include "define.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <regex.h>
# include <float.h>

typedef enum				e_token
{
	e_comments_t,
	e_vert_t,
	e_face_t,
	e_text_vert_t,
	e_norm_vert_t,
	e_usemtl_t,
	e_mtllib_t,
	e_coord_t,
	e_face_v_t,
	e_name_t,
	e_empty_t
}							t_token_e;

typedef struct				s_token
{
	t_token_e	type;
	char		*regex;
	int8_t		need_data;
	const char	*name;
}							t_token;

# define V_STEP 11

typedef struct				s_obj
{
	t_vect3	*v;
	t_vect2	*vt;
	t_vect3	*vn;
	int		v_max_size;
	int		v_nb_item;
	int		vt_max_size;
	int		vt_nb_item;
	int		vn_max_size;
	int		vn_nb_item;
	int		f_type;
	float	*verts;
	int		verts_max_size;
	int		verts_nb_item;
}							t_obj;

typedef enum				e_vert_type
{
	e_vp,
	e_vn,
	e_vt
}							t_vert_type;

typedef struct				s_vertex
{
	t_vect3	p;
	t_vect3	n;
	t_vect2	t;
}							t_vertex;

typedef struct				s_token_l
{
	t_token_e			type;
	char				*data;
	struct s_token_l	*next;
}							t_token_l;

static const t_token		g_token_reg[] =
{
	{e_comments_t, "^#.*$", FALSE, "comments"},
	{e_vert_t, "^v$", FALSE, "vert"},
	{e_face_t, "^f$", FALSE, "face"},
	{e_text_vert_t, "^vt$", FALSE, "text_vert"},
	{e_norm_vert_t, "^vn$", FALSE, "norm_vert"},
	{e_usemtl_t, "^usemtl$", FALSE, "usemtl"},
	{e_mtllib_t, "^mtllib$", FALSE, "mtllib"},
	{e_coord_t, "^-?[0-9]+\\.[0-9]+$", TRUE, "coord"},
	{e_face_v_t, "^[1-9]+[0-9]*((\\/[1-9]+[0-9]*(\\/[1-9]+[0-9]*)?)"
		"|(\\/\\/[1-9]+[0-9]*))?$", TRUE, "face_v"},
	{e_name_t, "^[^[:space:]]+$", TRUE, "name"}
};

int8_t						parse_vert(t_token_l *lst, t_obj *obj);
int8_t						parse_face(t_token_l *lst, t_obj *obj);
int8_t						parse_text_vert(t_token_l *lst, t_obj *obj);
int8_t						parse_norm_vert(t_token_l *lst, t_obj *obj);
int8_t						parse_usemtl(t_token_l *lst, t_obj *obj);
int8_t						parse_mtllib(t_token_l *lst, t_obj *obj);

typedef int8_t	(*t_parse_func)(t_token_l *lst, t_obj *obj);

typedef struct				s_token_func
{
	t_parse_func	func;
	t_token_e		arg_type;
	int				min;
	int8_t			accept_more;
}							t_token_func;

static const t_token_func	g_token_func[] =
{
	{NULL, e_empty_t, 0, FALSE},
	{&parse_vert, e_coord_t, 3, FALSE},
	{&parse_face, e_face_v_t, 3, TRUE},
	{&parse_text_vert, e_coord_t, 2, FALSE},
	{&parse_norm_vert, e_coord_t, 3, FALSE},
	{&parse_usemtl, e_name_t, 1, FALSE},
	{&parse_mtllib, e_name_t, 1, FALSE},
	{NULL, e_empty_t, 0, FALSE},
	{NULL, e_empty_t, 0, FALSE},
	{NULL, e_empty_t, 0, FALSE},
	{NULL, e_empty_t, 0, FALSE}
};

int8_t						parse_obj(const char *filename, t_obj *obj);
int8_t						lexer(const char *filename, t_token_l **lst, int \
*res_size);
void						free_reg(regex_t *regex, int nb_reg);
int8_t						compile_reg(regex_t *regex, int nb_reg);
int8_t						add_token(t_token_l *crnt, const char *word, \
int reti, int t);
void						init_token_l(t_token_l *lst, int res_size);
int8_t						realloc_tokens(t_token_l **lst, int *res_size);
void						free_token_list(t_token_l **lst, int res_size);
void						print_token_list(t_token_l *lst, int res_size);
void						free_obj(t_obj *obj);
void						norm_device_coord(t_obj *obj);
int8_t						check_grammar(t_token_l *lst, int *count);
int8_t						fill_vertex(t_obj *obj, t_vertex *v, int id, \
t_vert_type v_type);
void						init_v(t_vertex *v);
int8_t						fill_obj_verts(t_obj *obj, t_vertex *v);
void						check_type(int *type, t_token_l *crnt);
int8_t						check_face_grammar(t_token_l *lst, t_obj *obj);
t_vect3						calc_face_norm(t_vect3 p1, t_vect3 p2, t_vect3 p3);
int8_t						add_vt(t_obj *obj, char *v_str);
int8_t						register_triangle(t_obj *obj, t_token_l *a, \
t_token_l *b, t_token_l *c);
void						register_color(t_obj *obj, int grayscale);

#endif
