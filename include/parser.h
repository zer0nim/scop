/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:49:38 by emarin            #+#    #+#             */
/*   Updated: 2019/08/30 12:27:07 by emarin           ###   ########.fr       */
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

typedef struct				s_obj
{
	t_vect3	*v;
	t_vect2	*vt;
	t_vect3	*vn;
}							t_obj;

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
	{e_coord_t, "^-?[0-9]+.[0-9]+$", TRUE, "coord"},
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



int8_t						parse_obj(const char *filename);
int8_t						lexer(const char *filename, t_token_l **lst, int \
*res_size);
void						free_reg(regex_t *regex, int nb_reg);
int8_t						compile_reg(regex_t *regex, int nb_reg);
void						init_token_l(t_token_l *lst, int res_size);
int8_t						realloc_tokens(t_token_l **lst, int *res_size);
void						free_token_list(t_token_l **lst, int res_size);
void						print_token_list(t_token_l *lst, int res_size);

int8_t						check_grammar(t_token_l *lst);

#endif
