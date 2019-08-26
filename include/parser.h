/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 14:49:38 by emarin            #+#    #+#             */
/*   Updated: 2019/08/26 17:36:04 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "define.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

int8_t	lexer(const char *filename);

// #	Comments

// each tokens separated by [\t ]*

// v	Geometric vertices
//	->	v x y z
// vt	Texture vertices
//	->	vt u v
// vn	Vertex normals
//	->	vn x y z
// f	Face
//	->	f f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3] ...
// usemtl	Material name
//	->	usemtl mtlName
// mtllib	Material library
//	->	mtllib mtlFile

// x, y, z, u, v, ...:
//	-> -?[0-9]+(.[0-9]+)?

// mtlFile || mtlName:
//	-> \S+



// use sort of getNextWord

typedef enum	e_token
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
}				t_token_e;

typedef struct	s_token
{
	t_token_e	type;
	char		*data;
}				t_token;

// comments:	"^#.*$"
// vert:		"^v$"
// face:		"^f$"
// text_vert:	"^vt$"
// norm_vert:	"^vn$"
// usemtl:		"^usemtl$"
// mtllib:		"^mtllib$"
// coord:		"^-?[0-9]+.[0-9]+?$"
// face_v:		"^[1-9]+[0-9]*((\\/[1-9]+[0-9]*(\\/[1-9]+[0-9]*)?)|(\\/\\/[1-9]+[0-9]*))?$"
// name:		"^\\S+$"

#endif
