/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:30:26 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 05:28:11 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_coord	iter_mandelbrot(t_coord *z, t_coord *c)
{
	t_coord res;	
	res.x = pow(z->x, 2) - pow(z->y, 2) + c->x; 
	res.y = 2 * z->x * z->y + c->y; 
	return (res);
}

int	calc_iterations(t_data *data, t_coord *z, t_coord *c)
{
	int i = 0;
	t_coord new_z;
	
	new_z.x = z->x;
	new_z.y = z->y;
	while ((pow(new_z.y, 2) + pow(new_z.x, 2) + c->y + c->x) < 4 && i < data->quality)
		if (data->quality - 1 == i++)
			return (data->quality);
		else if (data->frac_type == MANDELBROT)
			new_z = iter_mandelbrot(&new_z, c);
	return (i);
}

double	re_scale(int num, double zoom, double inc, int scale)
{
	return (((num * scale) - 2) / (zoom + inc));
}

void	draw(t_data *data)
{
	int x;	
	int y;
	t_coord coord;
	int iter;

	y = -1;
	while (++y < HEIGHT)
	{
		coord.y = re_scale(y, data->zoom, data->inc_y, data->scale_y);
		x = -1;
		while (++x < WIDTH)
		{
			coord.x = re_scale(x, data->zoom, data->inc_x, data->scale_x);
			iter = calc_iterations(data, (t_coord *){0,0}, &coord);
			if (iter >= data->quality)
			{
				/* code */
			}
		}
	}
	
}
