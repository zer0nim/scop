/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:49:38 by emarin            #+#    #+#             */
/*   Updated: 2019/08/26 18:05:07 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "define.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

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
	e_name_t
}						t_token_e;

typedef struct			s_token
{
	t_token_e	type;
	char		*data;
}						t_token;

static const t_token	g_token_reg[] =
{
	{e_comments_t, "^#.*$"},
	{e_vert_t, "^v$"},
	{e_face_t, "^f$"},
	{e_text_vert_t, "^vt$"},
	{e_norm_vert_t, "^vn$"},
	{e_usemtl_t, "^usemtl$"},
	{e_mtllib_t, "^mtllib$"},
	{e_coord_t, "^-?[0-9]+.[0-9]+?$"},
	{e_face_v_t, "^[1-9]+[0-9]*((\\/[1-9]+[0-9]*(\\/[1-9]+[0-9]*)?)"
		"|(\\/\\/[1-9]+[0-9]*))?$"},
	{e_name_t, "^\\S+$"}
};

int8_t					lexer(const char *filename);

#endif
