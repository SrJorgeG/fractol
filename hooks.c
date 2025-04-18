/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:42:49 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/18 07:33:52 by jgomez-d         ###   ########.fr       */
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
	else if (keysym == XK_Right)
		data->inc_x += 0.2;
	else if (keysym == XK_Left)
		data->inc_x -= 0.2;
	else if (keysym == XK_Up)
		data->inc_y -= 0.2;
	else if (keysym == XK_Down)
		data->inc_y += 0.2;
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
	draw(data);
	return (0);
}
