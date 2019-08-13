/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:01:52 by emarin            #+#    #+#             */
/*   Updated: 2019/08/13 20:28:45 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int				next_index(t_tga_orig_info orig, int step, int8_t reset)
{
	static int	y = -1;
	static int	x = -1;
	int			y_copy;
	int			x_copy;

	if (y == -1 || reset)
		y = orig.y_start;
	if (x == -1 || reset)
		x = orig.x_start;
	if (reset)
		return -1;
	if (y == orig.y_end)
	{
		y = orig.y_start;
		x = orig.x_start;
	}
	if (x == orig.x_end)
	{
		x = orig.x_start;
		y += orig.y_step;
	}
	y_copy = y;
	x_copy = x;
	x += orig.x_step;
	return ((x_copy + orig.w * y_copy) * step);
}

void			read_tga16bits(t_tga_orig_info orig, FILE *fp
, t_texture_info *text_info)
{
	int			y;
	int			x;
	u_int16_t	color;

	printf("1\n");
	y = orig.y_start;
	while (y != orig.y_end)
	{
		x = orig.x_start;
		while (x != orig.x_end)
		{
			color = fgetc(fp) + (fgetc(fp) << 8);
			text_info->texels[(x + orig.w * y) * 3 + 0] = (color & 0x7C00) >> 7;
			text_info->texels[(x + orig.w * y) * 3 + 1] = (color & 0x03E0) >> 2;
			text_info->texels[(x + orig.w * y) * 3 + 2] = (color & 0x001F) << 3;

			x += orig.x_step;
		}
		y += orig.y_step;
	}
}

void			read_tga24_32bits(t_tga_orig_info orig, FILE *fp
, t_texture_info *text_info, int8_t is_32)
{
	int			i;
	int			index;
	int8_t		step;

	printf("2\n");
	printf("is_32: %d\n", is_32);
	step = (is_32) ? 4 : 3;
	i = -1;
	while (++i < (text_info->w * text_info->h))
	{
		index = next_index(orig, step, FALSE);
		text_info->texels[index + 2] = (uint8_t)fgetc(fp);
		text_info->texels[index + 1] = (uint8_t)fgetc(fp);
		text_info->texels[index + 0] = (uint8_t)fgetc(fp);
		if (is_32)
			text_info->texels[index + 3] = (uint8_t)fgetc(fp);
		// printf("index: %d\n", index);
	}
}

void			read_tga16bits_rle(t_tga_orig_info orig, FILE *fp
, t_texture_info *text_info)
{
	int			i;
	int			size;
	u_int16_t	color;
	uint8_t		packet_header;
	uint8_t		*ptr;

	(void)orig;
	printf("3\n");
	ptr = text_info->texels;
	while (ptr < text_info->texels + (text_info->w * text_info->h) * 3)
	{
		// read the first byte
		packet_header = fgetc(fp);
		size = 1 + (packet_header & 0x7f);

		// first bit indicate
		// equal consecutive byte field, first val: numbers, second val: values
		if (packet_header & 0x80)
		{
			color = fgetc(fp) + (fgetc(fp) << 8);

			i = 0;
			while (i < size)
			{
				ptr[0] = (uint8_t)(((color & 0x7C00) >> 10) << 3);
				ptr[1] = (uint8_t)(((color & 0x03E0) >> 5) << 3);
				ptr[2] = (uint8_t)(((color & 0x001F) >> 0) << 3);
				++i;
				ptr += 3;
			}
		}
		else
		{
			i = 0;
			while (i < size)
			{
				color = fgetc(fp) + (fgetc(fp) << 8);

				ptr[0] = (uint8_t)(((color & 0x7C00) >> 10) << 3);
				ptr[1] = (uint8_t)(((color & 0x03E0) >> 5) << 3);
				ptr[2] = (uint8_t)(((color & 0x001F) >> 0) << 3);
				++i;
				ptr += 3;
			}
		}
	}
}

void			read_tga24_32bits_rle(t_tga_orig_info orig, FILE *fp
, t_texture_info *text_info, int8_t is_32)
{
	int		i;
	int		size;
	uint8_t	rgba[4];
	uint8_t	packet_header;
	uint8_t	*ptr;
	int8_t	step;

	int		index;

	(void)orig;
	printf("4\n");
	ptr = text_info->texels;
	step = (is_32) ? 4 : 3;
	while (ptr < text_info->texels + (text_info->w * text_info->h * step))
	{
		// read first byte
		packet_header = (uint8_t)fgetc(fp);
		size = 1 + (packet_header & 0x7f);

		// first bit indicate
		// equal consecutive byte field, first val: numbers, second val: values
		if (packet_header & 0x80)
		{
			fread(rgba, sizeof(uint8_t), step, fp);

			i = 0;
			while (i < size)
			{
				index = next_index(orig, step, FALSE);
				text_info->texels[index + 0] = rgba[2];
				text_info->texels[index + 1] = rgba[1];
				text_info->texels[index + 2] = rgba[0];
				if (is_32)
					text_info->texels[index + 3] = rgba[3];
				++i;
				ptr += step;
			}
		}
		else
		{
			i = 0;
			while (i < size)
			{
				index = next_index(orig, step, FALSE);
				text_info->texels[index + 2] = (uint8_t)fgetc(fp);
				text_info->texels[index + 1] = (uint8_t)fgetc(fp);
				text_info->texels[index + 0] = (uint8_t)fgetc(fp);
				if (is_32)
					text_info->texels[index + 3] = (uint8_t)fgetc(fp);
				++i;
				ptr += step;
			}
		}
	}
}

t_tga_orig_info	get_tga_read_info(t_tga_header *header) {
	t_tga_orig_info	res;
	int32_t			orig_flag;

	res.w = header->w;
	orig_flag = (header->image_descriptor & TGA_ORIG_MASK) >> TGA_ORIG_SHIFT;

	if (orig_flag == TGA_ORIG_UR)
		printf("TGA_ORIG_UR\n");
	if (orig_flag == TGA_ORIG_BR)
		printf("TGA_ORIG_BR\n");
	if (orig_flag == TGA_ORIG_UL)
		printf("TGA_ORIG_UL\n");
	if (orig_flag == TGA_ORIG_BL)
		printf("TGA_ORIG_BL\n");

	if (orig_flag == TGA_ORIG_UR || orig_flag == TGA_ORIG_BR)
	{
		res.x_start = header->w - 1;
		res.x_step = - 1;
		res.x_end = - 1;
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

int8_t			read_texels(t_texture_info *text_info, t_tga_header *header
, FILE *fp)
{
	t_tga_orig_info	orig;

	orig = get_tga_read_info(header);

	if (!(text_info->texels = (uint8_t *)malloc(sizeof(uint8_t)
	* text_info->w * text_info->h * text_info->internal_format)))
		return (FALSE);

	if (header->data_type_code == T_BGR_16_24_32_BITS)
	{
		if (header->bits_per_pixel == 16)
			read_tga16bits(orig, fp, text_info);
		else if (header->bits_per_pixel == 24
		|| header->bits_per_pixel == 32)
			read_tga24_32bits(orig, fp, text_info, (header->bits_per_pixel == 32));
		else
			return (FALSE);
	}
	else if (header->data_type_code == T_BGR_16_24_32_BITS_RLE)
	{
		if (header->bits_per_pixel == 16)
			read_tga16bits_rle(orig, fp, text_info);
		else if (header->bits_per_pixel == 24
		|| header->bits_per_pixel == 32)
			read_tga24_32bits_rle(orig, fp, text_info, (header->bits_per_pixel
			== 32));
		else
			return (FALSE);
	}
	return (TRUE);
}

int8_t			get_texture_info(t_tga_header *header
, t_texture_info *text_info)
{
	text_info->w = header->w;
	text_info->h = header->h;

	if (header->data_type_code != T_BGR_16_24_32_BITS
	&& header->data_type_code != T_BGR_16_24_32_BITS_RLE)
	{
		fprintf(stderr, "Unhandled tga type");
		return (FALSE);
	}

	// 8 bits and 16 bits images will be converted to 24 bits
	if (header->bits_per_pixel <= 24)
	{
		text_info->format = GL_RGB;
		text_info->internal_format = 3;
	}
	else // 32 bits
	{
		text_info->format = GL_RGBA;
		text_info->internal_format = 4;
	}
	return (TRUE);
}

t_texture_info	*read_tga_file(const char *filename)
{
	FILE			*fp;
	t_texture_info	*text_info;
	t_tga_header	header;

	fp = fopen(filename, "rb");
	if (!fp)
	{
		fprintf(stderr, "Error while opening \"%s\"\n", filename);
		return (NULL);
	}

	// read header
	fread(&header, sizeof(t_tga_header), 1, fp);

	// fill texture infos
	if (!(text_info = (t_texture_info *)malloc(sizeof(t_texture_info))))
		return (NULL);
	if (!get_texture_info(&header, text_info))
	{
		free(text_info);
		return (NULL);
	}

	// read texels
	fseek(fp, header.id_lenght, SEEK_CUR);
	if (!read_texels(text_info, &header, fp))
	{
		free(text_info);
		return (NULL);
	}

	fclose(fp);
	return (text_info);
}
