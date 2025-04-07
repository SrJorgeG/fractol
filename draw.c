/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:30:26 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 21:38:40 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_coord	mandelbrot_iterate(t_coord z, t_coord c)
{
	t_coord	result;

	result.x = z.x * z.x - z.y * z.y + c.x;
	result.y = 2 * z.x * z.y + c.y;
	return (result);
}

t_coord	burningship_iterate(t_coord z, t_coord c)
{
	t_coord	result;
	double	abs_real;
	double	abs_imag;

	abs_real = fabs(z.x);
	abs_imag = fabs(z.y);
	result.x = abs_real * abs_real - abs_imag * abs_imag + c.x;
	result.y = 2 * abs_real * abs_imag + c.y;
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
	i = 0;
	while ((zn.x * zn.x + zn.y * zn.y) < 4.0
		&& i < data->quality)
	{
		if (i == data->quality - 1)
			return (data->quality);
		zn = iterate(zn, constant);
		i++;
	}
	mod = sqrt(zn.x * zn.x + zn.y * zn.y);
	if (1.0f < log2(mod))
		smooth_iter = (double)i + 1 - log2(log2(mod));
	else
		smooth_iter = (double)i + 1 - log2(1.0f);
	return (smooth_iter);
}

double	calculate_fractal( t_data *data, t_coord	coord)
{
	if (data->frac_type == MANDELBROT)
		return (compute_iterations((t_coord){0, 0}
			, coord, data, mandelbrot_iterate));
	/* else if (data->frac_type == JULIA)
	{
		return (compute_iterations(coord,
				(t_coord){data->julia_c_real, data->julia_c_imag},
			data, mandelbrot_iterate));
	} */
	return (0);
}

double	re_scale(int num, double zoom, double inc, int scale)
{
	return (((num * scale) - 2) / zoom + inc);
}

void	draw(t_data *data)
{
	int		x;	
	int		y;
	t_coord	coord;
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
				set_pixel_color(data->img_data, x, y, data->pallete[data->fill_index]);
			else
				set_pixel_color(data->img_data, x, y,
					smooth_color(iter, data->quality, data));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img_data->img, 0, 0);
}
