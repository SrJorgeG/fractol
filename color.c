/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:46:40 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	grey_color(double smooth_iter, t_data *data)
{
	t_color	c;
	int		i;
	double	t;
	double	pos;

	pos = smooth_iter / data->max_iter * 8;
	t = pos - (int)pos;
	i = ((int)pos + data->fill_index) % 8;
	if (i >= data->fill_index)
		i++;
	c.r = (int)((data->pallete[i] >> 16 & 0xFF) + ((data->pallete[(i + 1)
						% 9] >> 16 & 0xFF) - (data->pallete[i] >> 16 & 0xFF)) * t);
	c.g = (int)((data->pallete[i] >> 8 & 0xFF) + ((data->pallete[(i + 1)
						% 9] >> 8 & 0xFF) - (data->pallete[i] >> 8 & 0xFF)) * t);
	c.b = (int)((data->pallete[i] & 0xFF) + ((data->pallete[(i + 1) % 9]
					& 0xFF) - (data->pallete[i] & 0xFF)) * t);
	return ((c.r << 16) | (c.g << 8) | c.b);
}

static int	cosine_color(double smooth_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = sqrt(smooth_iter) * 0.15;
	r = (int)(255 * (0.5 + 0.5 * cos(6.28318 * (t + 0.00))));
	g = (int)(255 * (0.5 + 0.5 * cos(6.28318 * (t + 0.10))));
	b = (int)(255 * (0.5 + 0.5 * cos(6.28318 * (t + 0.20))));
	return ((r << 16) | (g << 8) | b);
}

static int	apply_shift(int color, t_color shift)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16 & 0xFF) + shift.r) & 0xFF;
	g = ((color >> 8 & 0xFF) + shift.g) & 0xFF;
	b = ((color & 0xFF) + shift.b) & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

int	pixel_color(double smooth_iter, t_data *data)
{
	int	color;

	if (data->palette_mode == GREY)
	{
		if (smooth_iter >= data->max_iter)
			color = data->pallete[data->fill_index];
		else
			color = grey_color(smooth_iter, data);
	}
	else if (smooth_iter >= data->max_iter)
		return (BLACK);
	else
		color = cosine_color(smooth_iter);
	return (apply_shift(color, data->shift));
}

void	set_pixel_color(t_imgdata *img_data, int x, int y, int color)
{
	int	offset;

	offset = (y * img_data->line_length) + (x * (img_data->bpp / 8));
	*(unsigned int *)(img_data->addr + offset) = color;
}
