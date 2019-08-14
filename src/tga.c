/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:01:52 by emarin            #+#    #+#             */
/*   Updated: 2019/08/14 15:11:10 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

t_tga_orig_info	get_tga_read_info(t_tga_header *header)
{
	t_tga_orig_info	res;
	int32_t			orig_flag;

	res.w = header->w;
	orig_flag = (header->image_descriptor & TGA_ORIG_MASK) >> TGA_ORIG_SHIFT;
	if (orig_flag == TGA_ORIG_UR || orig_flag == TGA_ORIG_BR)
	{
		res.x_start = header->w - 1;
		res.x_step = -1;
		res.x_end = -1;
		res.y_start = (orig_flag == TGA_ORIG_UR) ? header->h - 1 : 0;
		res.y_step = (orig_flag == TGA_ORIG_UR) ? -1 : 1;
		res.y_end = (orig_flag == TGA_ORIG_UR) ? -1 : header->h;
		return (res);
	}
	res.x_start = 0;
	res.x_step = 1;
	res.x_end = header->w;
	res.y_start = (orig_flag == TGA_ORIG_UL) ? header->h - 1 : 0;
	res.y_step = (orig_flag == TGA_ORIG_UL) ? -1 : 1;
	res.y_end = (orig_flag == TGA_ORIG_UL) ? -1 : header->h;
	return (res);
}

int8_t			read_texels(t_texture_info *txt_i, t_tga_header *header
, FILE *fp, t_tga_orig_info orig)
{
	next_index(orig, 3, TRUE);
	if (!(txt_i->texels = (uint8_t *)malloc(sizeof(uint8_t)
	* txt_i->w * txt_i->h * txt_i->internal_format)))
		return (FALSE);
	if (header->data_type_code == T_BGR_16_24_32_BITS)
	{
		if (header->bits_per_pixel == 16)
			read_tga16bits(orig, fp, txt_i);
		else if (header->bits_per_pixel == 24 || header->bits_per_pixel == 32)
			read_tga24_32bits(orig, fp, txt_i, (header->bits_per_pixel == 32));
		else
			return (FALSE);
	}
	else if (header->data_type_code == T_BGR_16_24_32_BITS_RLE)
	{
		if (header->bits_per_pixel == 16)
			read_tga16bits_rle(orig, fp, txt_i);
		else if (header->bits_per_pixel == 24 || header->bits_per_pixel == 32)
			read_tga24_32bits_rle(orig, fp, txt_i, (header->bits_per_pixel
			== 32));
		else
			return (FALSE);
	}
	return (TRUE);
}

int8_t			get_texture_info(t_tga_header *header, t_texture_info *txt_i)
{
	txt_i->w = header->w;
	txt_i->h = header->h;
	if (header->data_type_code != T_BGR_16_24_32_BITS
	&& header->data_type_code != T_BGR_16_24_32_BITS_RLE)
	{
		fprintf(stderr, "Unhandled tga type");
		return (FALSE);
	}
	if (header->bits_per_pixel <= 24)
	{
		txt_i->format = GL_RGB;
		txt_i->internal_format = 3;
	}
	else
	{
		txt_i->format = GL_RGBA;
		txt_i->internal_format = 4;
	}
	return (TRUE);
}

t_texture_info	*read_tga_file(const char *filename)
{
	FILE			*fp;
	t_texture_info	*txt_i;
	t_tga_header	header;

	if (!(fp = fopen(filename, "rb")))
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (NULL);
	}
	fread(&header, sizeof(t_tga_header), 1, fp);
	if (!(txt_i = (t_texture_info *)malloc(sizeof(t_texture_info))))
		return (NULL);
	if (!get_texture_info(&header, txt_i))
	{
		free(txt_i);
		return (NULL);
	}
	fseek(fp, header.id_lenght, SEEK_CUR);
	if (!read_texels(txt_i, &header, fp, get_tga_read_info(&header)))
	{
		free(txt_i);
		return (NULL);
	}
	fclose(fp);
	return (txt_i);
}
