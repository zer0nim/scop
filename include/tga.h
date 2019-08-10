/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 14:13:14 by emarin            #+#    #+#             */
/*   Updated: 2019/08/10 15:13:08 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

# include "scop.h"

typedef struct		s_texture_info
{
	int32_t	width;
	int32_t	height;
	int32_t	format;
	int32_t	internal_format;
	int32_t	id;
	uint8_t	*texels;
}					t_texture_info;


#pragma pack(push, 1)
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

	uint16_t	width;
	uint16_t	height;

	uint8_t		bits_per_pixel;
	uint8_t		image_descriptor;
}					t_tga_header;
#pragma pack(pop)

# define T_BGR_16_24_32_BITS 2
# define T_BGR_16_24_32_BITS_RLE 10

#endif