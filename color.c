/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:46:40 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/18 07:40:03 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	palette_color(double smooth_iter, double max_iter, t_data *data)
{
	t_color	color;
	int		i;
	double	t;

	t = (smooth_iter / max_iter * 8) - (int)(smooth_iter / max_iter * 8);
	i = ((int)(smooth_iter / max_iter * 8) + data->fill_index) % 9;
	if (i >= data->fill_index)
		i++;
	color.r = (int)((data->pallete[i] >> 16 & 0xFF)
			+ ((data->pallete[(i + 1) % 9] >> 16 & 0xFF)
				- (data->pallete[i] >> 16 & 0xFF)) * t);
	color.g = (int)((data->pallete[i] >> 8 & 0xFF)
			+ ((data->pallete[(i + 1) % 9] >> 8 & 0xFF)
				- (data->pallete[i] >> 8 & 0xFF)) * t);
	color.b = (int)((data->pallete[i] & 0xFF)
			+ ((data->pallete[(i + 1) % 9] & 0xFF)
				- (data->pallete[i] & 0xFF)) * t);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

int	smooth_color(double smooth_iter, double max_iter, t_data *data)
{
	if (smooth_iter >= max_iter)
		return (data->fill_color);
	else
		return (palette_color(smooth_iter, max_iter, data));
}

double	scale_num(int num, double zoom, double scale, double added)
{
	return (((num * scale) - 2.0) / zoom + added);
}

void	set_pixel_color(t_imgdata *img_data, int x, int y, int color)
{
	int	offset;

	offset = (y * img_data->line_length) + (x * (img_data->bpp / 8));
	*(unsigned int *)(img_data->addr + offset) = color;
}

void	init_pallete(t_data *data)
{
	data->pallete[8] = 0x000000;
	data->pallete[7] = 0x222222;
	data->pallete[6] = 0x444444;
	data->pallete[5] = 0x666666;
	data->pallete[4] = 0x888888;
	data->pallete[3] = 0xAAAAAA;
	data->pallete[2] = 0xDDDDDD;
	data->pallete[1] = 0xEEEEEE;
	data->pallete[0] = 0xFFFFFF;
	data->fill_color = data->pallete[data->fill_index];
}

//	data->pallete[0] = 0x000000;
// 	data->pallete[1] = 0xFF0000;
// 	data->pallete[2] = 0x00FF00;
// 	data->pallete[3] = 0x0000FF;
// 	data->pallete[4] = 0xFFFF00;
// 	data->pallete[5] = 0xFF00FF;
// 	data->pallete[6] = 0x00FFFF;
// 	data->pallete[7] = 0xFF6600;
// 	data->pallete[8] = 0xFFFFFF;
