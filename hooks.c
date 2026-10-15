/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 05:42:49 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	good_exit(t_data *data)
{
	cleanup(data, 0);
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
	cord_x = re_scale(x, old_zoom, data->inc_x, data->scale_x);
	cord_y = re_scale(y, old_zoom, data->inc_y, data->scale_y);
	data->inc_x = cord_x - ((x * data->scale_x - 2.0) / data->zoom);
	data->inc_y = cord_y - ((y * data->scale_y - 2.0) / data->zoom);
	draw(data);
	return (0);
}

int	motion_hook(int x, int y, t_data *data)
{
	if (!data->julia_live || data->frac_type != JULIA)
		return (0);
	data->j_c_real = x * data->scale_x - 2.0;
	data->j_c_i = y * data->scale_y - 2.0;
	draw(data);
	return (0);
}

static void	toggle_keys(int keysym, t_data *data)
{
	if (keysym == XK_p || keysym == XK_P)
		data->palette_mode = !data->palette_mode;
	else if (keysym == XK_h || keysym == XK_H)
		data->show_help = !data->show_help;
	else if (keysym == XK_j || keysym == XK_J)
	{
		data->julia_live = !data->julia_live;
		if (data->julia_live)
			data->frac_type = JULIA;
	}
	else if (keysym == XK_r || keysym == XK_R)
		reset_values(data);
	else if (keysym == XK_Tab)
	{
		data->frac_type = (data->frac_type + 1) % 3;
		reset_values(data);
	}
}

int	key_hooks(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		good_exit(data);
	else if (keysym == XK_Right || keysym == XK_Left)
		data->inc_x += (0.2 - 0.4 * (keysym == XK_Left)) / data->zoom;
	else if (keysym == XK_Up || keysym == XK_Down)
		data->inc_y -= (0.2 - 0.4 * (keysym == XK_Down)) / data->zoom;
	else if ((keysym == XK_plus || keysym == XK_KP_Add
			|| keysym == XK_equal) && data->quality < MAX_ITER)
		data->quality *= 1.1;
	else if ((keysym == XK_minus || keysym == XK_KP_Subtract)
		&& data->quality > 4)
		data->quality *= 0.9;
	else if (keysym == XK_c || keysym == XK_C)
		shift_color(data, 0);
	else if (keysym == XK_v || keysym == XK_V)
		shift_color(data, 1);
	else if (keysym == XK_b || keysym == XK_B)
		shift_color(data, 2);
	else
		toggle_keys(keysym, data);
	draw(data);
	return (0);
}
