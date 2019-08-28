/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:49:38 by emarin            #+#    #+#             */
/*   Updated: 2019/08/28 15:42:35 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "define.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <regex.h>

typedef enum			e_token
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
}						t_token_e;

typedef struct			s_token
{
	t_token_e	type;
	char		*regex;
	int8_t		need_data;
	const char	*name;
}						t_token;

typedef struct			s_token_l
{
	t_token_e			type;
	char				*data;
	struct s_token_l	*next;
}						t_token_l;

static const t_token	g_token_reg[] =
{
	{e_comments_t, "^#.*$", FALSE, "comments",},
	{e_vert_t, "^v$", FALSE, "vert",},
	{e_face_t, "^f$", FALSE, "face",},
	{e_text_vert_t, "^vt$", FALSE, "text_vert",},
	{e_norm_vert_t, "^vn$", FALSE, "norm_vert",},
	{e_usemtl_t, "^usemtl$", FALSE, "usemtl",},
	{e_mtllib_t, "^mtllib$", FALSE, "mtllib",},
	{e_coord_t, "^-?[0-9]+.[0-9]+$", TRUE, "coord",},
	{e_face_v_t, "^[1-9]+[0-9]*((\\/[1-9]+[0-9]*(\\/[1-9]+[0-9]*)?)"
		"|(\\/\\/[1-9]+[0-9]*))?$", TRUE, "face_v",},
	{e_name_t, "^[^[:space:]]+$", TRUE, "name"}
};

int8_t					lexer(const char *filename);

#endif
