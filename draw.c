/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:30:26 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/19 00:22:05 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_coord	iterate(t_coord z, t_coord c)
{
	t_coord	result;

	result.x = z.x * z.x - z.y * z.y + c.x;
	result.y = 2 * z.x * z.y + c.y;
	return (result);
}

double	compute_iterations(t_coord variable, t_coord constant, t_data *data,
						t_coord (*iterate)(t_coord, t_coord))
{
	int		i;
	t_coord	zn;
	double	smooth_iter;
	double	mod;

	zn = variable;
	i = -1;
	while ((zn.x * zn.x + zn.y * zn.y) < 4.0
		&& ++i < data->quality)
	{
		if (data->frac_type == BSHIP)
		{
			zn.x = fabs(zn.x);
			zn.y = fabs(zn.y);
		}
		if (i == data->quality - 1)
			return (data->quality);
		zn = iterate(zn, constant);
	}
	mod = sqrt(zn.x * zn.x + zn.y * zn.y);
	if (1.0f < log2(mod))
		smooth_iter = (double)i + 1 - log2(log2(mod));
	else
		smooth_iter = (double)i + 1 - log2(1.0f);
	return (smooth_iter);
}

double	calculate_fractal( t_data *data, t_coord coord)
{
	if (data->frac_type == MANDELBROT)
		return (compute_iterations((t_coord){0, 0}
			, coord, data, iterate));
	else if (data->frac_type == JULIA)
	{
		return (compute_iterations(coord,
				(t_coord){data->j_c_real, data->j_c_i},
			data, iterate));
	}
	else if (data->frac_type == BSHIP)
		return (compute_iterations((t_coord){0, 0}
			, coord, data, iterate));
	return (0);
}

double	re_scale(int num, double zoom, double inc, double scale)
{
	return (((num * scale) - 2) / zoom + inc);
}

void	draw(t_data *data)
{
	int			x;	
	int			y;
	t_coord		coord;
	double		iter;

	y = -1;
	while (++y < HEIGHT)
	{
		coord.y = re_scale(y, data->zoom, data->inc_y, data->scale_y);
		x = -1;
		while (++x < WIDTH)
		{
			coord.x = re_scale(x, data->zoom, data->inc_x, data->scale_x);
			iter = calculate_fractal(data, coord);
			if (iter >= data->quality)
				set_pixel_color(data->img_data, x, y,
					data->pallete[data->fill_index]);
			else
				set_pixel_color(data->img_data, x, y,
					smooth_color(iter, data->quality, data));
		}
	}
	data->frames++;
	mlx_put_image_to_window(data->mlx, data->win, data->img_data->img, 0, 0);
}
