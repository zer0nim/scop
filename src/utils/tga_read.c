/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emarin <emarin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:11:49 by emarin            #+#    #+#             */
/*   Updated: 2019/08/14 15:12:10 by emarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int				next_index(t_tga_orig_info orig, int step, int8_t reset)
{
	static int	y = -1;
	static int	x = -1;
	int			x_copy;

	if (reset)
	{
		y = -1;
		x = -1;
		return (-1);
	}
	if (y == -1)
		y = orig.y_start;
	if (x == -1)
		x = orig.x_start;
	if (y == orig.y_end || x == orig.x_end)
	{
		y = (x == orig.x_end) ? y + orig.y_step : orig.y_start;
		x = orig.x_start;
	}
	x_copy = x;
	x += orig.x_step;
	return ((x_copy + orig.w * y) * step);
}

void			read_tga16bits(t_tga_orig_info orig, FILE *fp
, t_texture_info *txt_i)
{
	int			i;
	int			index;
	u_int16_t	color;

	i = -1;
	while (++i < (txt_i->w * txt_i->h))
	{
		color = fgetc(fp) + (fgetc(fp) << 8);
		index = next_index(orig, 3, FALSE);
		txt_i->texels[index + 0] = (color & 0x7C00) >> 7;
		txt_i->texels[index + 1] = (color & 0x03E0) >> 2;
		txt_i->texels[index + 2] = (color & 0x001F) << 3;
	}
}

void			read_tga24_32bits(t_tga_orig_info orig, FILE *fp
, t_texture_info *txt_i, int8_t is_32)
{
	int			i;
	int			index;
	int8_t		step;

	step = (is_32) ? 4 : 3;
	i = -1;
	while (++i < (txt_i->w * txt_i->h))
	{
		index = next_index(orig, step, FALSE);
		txt_i->texels[index + 2] = fgetc(fp);
		txt_i->texels[index + 1] = fgetc(fp);
		txt_i->texels[index + 0] = fgetc(fp);
		if (is_32)
			txt_i->texels[index + 3] = fgetc(fp);
	}
}

void			read_tga16bits_rle(t_tga_orig_info orig, FILE *fp
, t_texture_info *txt_i)
{
	int			size;
	u_int16_t	color;
	uint8_t		head;
	uint8_t		*ptr;
	int			index;

	ptr = txt_i->texels;
	while (ptr < txt_i->texels + (txt_i->w * txt_i->h) * 3)
	{
		head = fgetc(fp);
		size = 1 + (head & 0x7f);
		if (head & 0x80)
			color = fgetc(fp) + (fgetc(fp) << 8);
		while (size--)
		{
			if (!(head & 0x80))
				color = fgetc(fp) + (fgetc(fp) << 8);
			index = next_index(orig, 3, FALSE);
			txt_i->texels[index + 0] = (color & 0x7C00) >> 7;
			txt_i->texels[index + 1] = (color & 0x03E0) >> 2;
			txt_i->texels[index + 2] = (color & 0x001F) << 3;
			ptr += 3;
		}
	}
}

void			read_tga24_32bits_rle(t_tga_orig_info orig, FILE *fp
, t_texture_info *txt_i, int8_t is_32)
{
	int		size;
	uint8_t	rgba[4];
	uint8_t	head;
	uint8_t	*ptr;
	int		index;

	ptr = txt_i->texels;
	while (ptr < txt_i->texels + (txt_i->w * txt_i->h * ((is_32) ? 4 : 3)))
	{
		head = fgetc(fp);
		size = 1 + (head & 0x7f);
		if (head & 0x80)
			fread(rgba, sizeof(uint8_t), ((is_32) ? 4 : 3), fp);
		while (size--)
		{
			index = next_index(orig, ((is_32) ? 4 : 3), FALSE);
			txt_i->texels[index + 2] = (head & 0x80) ? rgba[0] : fgetc(fp);
			txt_i->texels[index + 1] = (head & 0x80) ? rgba[1] : fgetc(fp);
			txt_i->texels[index + 0] = (head & 0x80) ? rgba[2] : fgetc(fp);
			if (is_32)
				txt_i->texels[index + 3] = (head & 0x80) ? rgba[3] : fgetc(fp);
			ptr += ((is_32) ? 4 : 3);
		}
	}
}
