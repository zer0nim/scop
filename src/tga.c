/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:01:52 by emarin            #+#    #+#             */
/*   Updated: 2019/08/10 16:39:41 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

void			read_tga16bits(FILE *fp, t_texture_info *text_info)
{
	int			i;
	u_int16_t	color;

	i = 0;
	while (i < (text_info->width * text_info->height))
	{
		// color is coded in two bytes
		// each component is coded on 5 bits
		// the first left bit of these two bytes is not used
		color = fgetc(fp) + (fgetc(fp) << 8);

		// convert BGR to RGB
		// "<< 3" is used to convert from 0-31 to 0-255
		text_info->texels[(i * 3) + 0] = (uint8_t)(((color & 0x7C00) >> 10)
		<< 3);
		text_info->texels[(i * 3) + 1] = (uint8_t)(((color & 0x03E0) >> 5)
		<< 3);
		text_info->texels[(i * 3) + 2] = (uint8_t)(((color & 0x001F) >> 0)
		<< 3);
		++i;
	}
}

void			read_tga24_32bits(FILE *fp, t_texture_info *text_info
, int8_t is_32)
{
	int		i;
	int8_t	step;

	step = (is_32) ? 4 : 3;
	i = 0;
	while (i < (text_info->width * text_info->height))
	{
		// read and convert BGRA to RGBA
		text_info->texels[(i * step) + 2] = (uint8_t)fgetc(fp);
		text_info->texels[(i * step) + 1] = (uint8_t)fgetc(fp);
		text_info->texels[(i * step) + 0] = (uint8_t)fgetc(fp);
		if (is_32)
			text_info->texels[(i * step) + 3] = (uint8_t)fgetc(fp);
		++i;
	}
}

void			read_tga16bits_rle(FILE *fp, t_texture_info *text_info)
{
	int			i;
	int			size;
	u_int16_t	color;
	uint8_t		packet_header;
	uint8_t		*ptr;

	ptr = text_info->texels;
	while (ptr < text_info->texels + (text_info->width * text_info->height) * 3)
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

void			read_tga24_32bits_rle(FILE *fp, t_texture_info *text_info
, int8_t is_32)
{
	int		i;
	int		size;
	uint8_t	rgba[4];
	uint8_t	packet_header;
	uint8_t	*ptr;
	int8_t	step;

	ptr = text_info->texels;
	step = (is_32) ? 4 : 3;
	while (ptr < text_info->texels + (text_info->width * text_info->height)
	* step)
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
				ptr[0] = rgba[2];
				ptr[1] = rgba[1];
				ptr[2] = rgba[0];
				if (is_32)
					ptr[3] = rgba[3];
				++i;
				ptr += step;
			}
		}
		else
		{
			i = 0;
			while (i < size)
			{
				ptr[2] = (uint8_t)fgetc(fp);
				ptr[1] = (uint8_t)fgetc(fp);
				ptr[0] = (uint8_t)fgetc(fp);
				if (is_32)
					ptr[3] = (uint8_t)fgetc(fp);
				++i;
				ptr += step;
			}
		}
	}
}

int8_t			read_texels(t_texture_info *text_info, t_tga_header *header
, FILE *fp)
{
	if (!(text_info->texels = (uint8_t *)malloc(sizeof(uint8_t)
	* text_info->width * text_info->height * text_info->internal_format)))
		return (FALSE);

	if (header->data_type_code == T_BGR_16_24_32_BITS)
	{
		if (header->bits_per_pixel == 16)
			read_tga16bits(fp, text_info);
		else if (header->bits_per_pixel == 24
		|| header->bits_per_pixel == 32)
			read_tga24_32bits(fp, text_info, (header->bits_per_pixel == 32));
		else
			return (FALSE);
	}
	else if (header->data_type_code == T_BGR_16_24_32_BITS_RLE)
	{
		if (header->bits_per_pixel == 16)
			read_tga16bits_rle(fp, text_info);
		else if (header->bits_per_pixel == 24
		|| header->bits_per_pixel == 32)
			read_tga24_32bits_rle(fp, text_info, (header->bits_per_pixel
			== 32));
		else
			return (FALSE);
	}
	return (TRUE);
}

int8_t			get_texture_info(t_tga_header *header
, t_texture_info *text_info)
{
	text_info->width = header->width;
	text_info->height = header->height;

	if (header->data_type_code != T_BGR_16_24_32_BITS
	&& header->data_type_code != T_BGR_16_24_32_BITS_RLE)
	{
		fprintf(stderr, "Unhandled tga type");
		return (FALSE);
	}

	if (header->data_type_code == T_BGR_16_24_32_BITS_RLE)
	{
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
