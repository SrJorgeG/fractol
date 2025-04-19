/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:42:49 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/19 01:06:36 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	good_exit(t_data *data)
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
	exit(0);
	return (0);
}

void	reset_values(t_data *data)
{
	data->inc_x = 0.0;
	data->inc_y = 0.0;
	data->quality = QUALITY;
	data->zoom = 1.0;
	data->fill_index = 4;
	data->scale_x = 4.0 / WIDTH;
	data->scale_y = 4.0 / HEIGHT;
	data->j_c_real = 0.35;
	data->j_c_i = 0.35;
	init_pallete(data);
}

int	mouse_hooks(int button, int x, int y, t_data *data)
{
	double	cord_x;
	double	cord_y;
	double	old_zoom;

	old_zoom = data->zoom;
	if (button == Button5)
		data->zoom *= 0.9;
	else if (button == Button4)
		data->zoom *= 1.1;
	else
		return (0);
	cord_x = (x * data->scale_x - 2.0) / old_zoom + data->inc_x;
	cord_y = (y * data->scale_y - 2.0) / old_zoom + data->inc_y;
	data->inc_x = cord_x - ((x * data->scale_x - 2.0) / data->zoom);
	data->inc_y = cord_y - ((y * data->scale_y - 2.0) / data->zoom);
	draw(data);
	return (0);
}

int	key_hooks(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		good_exit(data);
	else if (keysym == XK_Right || keysym == XK_Left)
		data->inc_x += (0.2 - 0.4 * (keysym == XK_Left)) / data->zoom;
	else if (keysym == XK_Up || keysym == XK_Down)
		data->inc_y -= (0.2 - 0.4 * (keysym == XK_Down)) / data->zoom;
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		data->quality *= 1.1;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		data->quality *= 0.9;
	else if (keysym == XK_c || keysym == XK_C)
		change_pallete_r(data);
	else if (keysym == XK_v || keysym == XK_V)
		change_pallete_g(data);
	else if (keysym == XK_b || keysym == XK_B)
		change_pallete_b(data);
	else if (keysym == XK_r || keysym == XK_R)
		reset_values(data);
	else if (keysym == XK_Tab)
	{
		data->frac_type = (data->frac_type + 1) % 3;
		reset_values(data);
	}
	return (draw(data), 0);
}
