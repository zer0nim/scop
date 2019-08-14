/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 14:13:14 by emarin            #+#    #+#             */
/*   Updated: 2019/08/14 15:16:12 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

# include "scop.h"

typedef struct		s_texture_info
{
	int32_t		w;
	int32_t		h;
	int32_t		format;
	int32_t		internal_format;
	uint32_t	id;
	uint8_t		*texels;
}					t_texture_info;

typedef struct		s_tga_orig_info
{
	int32_t		w;
	int32_t		x_start;
	int32_t		x_step;
	int32_t		x_end;
	int32_t		y_start;
	int32_t		y_step;
	int32_t		y_end;
}					t_tga_orig_info;

# pragma pack(push, 1)

typedef struct		s_tga_header
{
	uint8_t		id_lenght;
	uint8_t		colormap_type;
	uint8_t		data_type_code;

	uint16_t	colormap_origin;
	uint16_t	colormap_length;
	uint8_t		colormap_depth;

	uint16_t	x_origin;
	uint16_t	y_origin;

	uint16_t	w;
	uint16_t	h;

	uint8_t		bits_per_pixel;
	uint8_t		image_descriptor;
}					t_tga_header;
# pragma pack(pop)

# define T_BGR_16_24_32_BITS 2
# define T_BGR_16_24_32_BITS_RLE 10

# define TGA_ORIG_MASK 0x30
# define TGA_ORIG_SHIFT 0x04
# define TGA_ORIG_BL 0x00
# define TGA_ORIG_BR 0x01
# define TGA_ORIG_UL 0x02
# define TGA_ORIG_UR 0x03

int					next_index(t_tga_orig_info orig, int step, int8_t reset);
void				read_tga16bits(t_tga_orig_info orig, FILE *fp\
, t_texture_info *txt_i);
void				read_tga24_32bits(t_tga_orig_info orig, FILE *fp\
, t_texture_info *txt_i, int8_t is_32);
void				read_tga16bits_rle(t_tga_orig_info orig, FILE *fp\
, t_texture_info *txt_i);
void				read_tga24_32bits_rle(t_tga_orig_info orig, FILE *fp\
, t_texture_info *txt_i, int8_t is_32);

t_texture_info		*read_tga_file(const char *filename);

#endif
