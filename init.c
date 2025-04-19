/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:34:08 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/19 00:48:09 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_exit(t_data *data)
{
	if (data->img_data)
	{
		if (data->img_data->img)
			mlx_destroy_image(data->mlx, data->img_data->img);
		free(data->img_data);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data)
		free(data);
	exit(1);
}

void	pre_init(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img_data = NULL;
	data->frac_type = 0;
	data->inc_x = 0.0;
	data->inc_y = 0.0;
	data->quality = QUALITY;
	data->zoom = 1.0;
	data->fill_index = 4;
	data->scale_x = 4.0 / WIDTH;
	data->scale_y = 4.0 / HEIGHT;
	data->j_c_real = 0.35;
	data->j_c_i = 0.35;
	data->frames = 0;
	init_pallete(data);
}

void	init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data);
	data->win = mlx_new_window(data->mlx, HEIGHT, WIDTH, "FRACTOL");
	if (!data->win)
		error_exit(data);
	data->img_data = ft_calloc(1, sizeof(t_imgdata));
	if (!data->img_data)
		error_exit(data);
	data->img_data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img_data->img)
		error_exit(data);
	data->img_data->addr = mlx_get_data_addr(data->img_data->img,
			&data->img_data->bpp,
			&data->img_data->line_length, &data->img_data->endian);
}
