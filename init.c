/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:34:08 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	cleanup(t_data *data, int code)
{
	if (data && data->img_data)
	{
		if (data->img_data->img)
			mlx_destroy_image(data->mlx, data->img_data->img);
		free(data->img_data);
	}
	if (data && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data && data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
	exit(code);
}

void	pre_init(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img_data = NULL;
	data->frac_type = MANDELBROT;
	data->palette_mode = VIVID;
	data->j_user_real = 0.35;
	data->j_user_i = 0.35;
	data->julia_live = 0;
	data->show_help = 1;
	reset_values(data);
}

void	reset_values(t_data *data)
{
	data->inc_x = 0.0;
	data->inc_y = 0.0;
	if (data->frac_type == MANDELBROT)
		data->inc_x = -0.5;
	else if (data->frac_type == BSHIP)
	{
		data->inc_x = -0.4;
		data->inc_y = -0.5;
	}
	data->quality = QUALITY;
	data->max_iter = QUALITY;
	data->zoom = 1.0;
	data->fill_index = 4;
	data->scale_x = 4.0 / WIDTH;
	data->scale_y = 4.0 / HEIGHT;
	data->j_c_real = data->j_user_real;
	data->j_c_i = data->j_user_i;
	data->shift = (t_color){0, 0, 0};
	init_pallete(data);
}

void	init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup(data, 1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FRACTOL");
	if (!data->win)
		cleanup(data, 1);
	data->img_data = ft_calloc(1, sizeof(t_imgdata));
	if (!data->img_data)
		cleanup(data, 1);
	data->img_data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img_data->img)
		cleanup(data, 1);
	data->img_data->addr = mlx_get_data_addr(data->img_data->img,
			&data->img_data->bpp,
			&data->img_data->line_length, &data->img_data->endian);
}
