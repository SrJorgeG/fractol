/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:30:26 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_coord	iterate(t_coord z, t_coord c, int abs_mode)
{
	t_coord	result;

	if (abs_mode)
	{
		z.x = fabs(z.x);
		z.y = fabs(z.y);
	}
	result.x = z.x * z.x - z.y * z.y + c.x;
	result.y = 2 * z.x * z.y + c.y;
	return (result);
}

double	compute_iterations(t_coord variable, t_coord constant, t_data *data)
{
	int		i;
	t_coord	zn;
	double	mod;

	zn = variable;
	i = 0;
	while ((zn.x * zn.x + zn.y * zn.y) < 4.0)
	{
		if (++i >= data->max_iter)
			return (data->max_iter);
		zn = iterate(zn, constant, data->frac_type == BSHIP);
	}
	mod = sqrt(zn.x * zn.x + zn.y * zn.y);
	if (log2(mod) > 1.0)
		return ((double)i + 1 - log2(log2(mod)));
	return ((double)i + 1);
}

static void	*render_rows(void *arg)
{
	t_thread	*th;
	t_data		*data;
	t_coord		coord;
	int			x;
	int			y;

	th = (t_thread *)arg;
	data = th->data;
	y = th->id;
	while (y < HEIGHT)
	{
		coord.y = re_scale(y, data->zoom, data->inc_y, data->scale_y);
		x = -1;
		while (++x < WIDTH)
		{
			coord.x = re_scale(x, data->zoom, data->inc_x, data->scale_x);
			if (data->frac_type == JULIA)
				set_pixel_color(data->img_data, x, y, pixel_color(
						compute_iterations(coord, (t_coord){data->j_c_real,
							data->j_c_i}, data), data));
			else
				set_pixel_color(data->img_data, x, y, pixel_color(
						compute_iterations((t_coord){0, 0}, coord, data),
						data));
		}
		y += NTHREADS;
	}
	return (NULL);
}

static void	update_max_iter(t_data *data)
{
	double	iter;

	iter = data->quality;
	if (data->zoom > 1.0)
		iter *= 1.0 + 0.25 * log2(data->zoom);
	if (iter > MAX_ITER)
		iter = MAX_ITER;
	if (iter < 2)
		iter = 2;
	data->max_iter = (int)iter;
}

void	draw(t_data *data)
{
	pthread_t	tid[NTHREADS];
	t_thread	th[NTHREADS];
	int			i;
	int			created;

	update_max_iter(data);
	i = -1;
	created = 0;
	while (++i < NTHREADS)
	{
		th[i] = (t_thread){data, i};
		if (pthread_create(&tid[i], NULL, render_rows, &th[i]) == 0)
			created |= 1 << i;
		else
			render_rows(&th[i]);
	}
	i = -1;
	while (++i < NTHREADS)
		if (created & (1 << i))
			pthread_join(tid[i], NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img_data->img, 0, 0);
	if (data->show_help)
		draw_controls(data);
}
