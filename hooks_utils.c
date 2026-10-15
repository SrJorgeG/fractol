/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 07:30:20 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_pallete(t_data *data)
{
	data->pallete[8] = 0x000000;
	data->pallete[7] = 0x222222;
	data->pallete[6] = 0x444444;
	data->pallete[5] = 0x666666;
	data->pallete[4] = 0x888888;
	data->pallete[3] = 0xAAAAAA;
	data->pallete[2] = 0xDDDDDD;
	data->pallete[1] = 0xEEEEEE;
	data->pallete[0] = 0xFFFFFF;
}

void	shift_color(t_data *data, int channel)
{
	if (channel == 0)
		data->shift.r = (data->shift.r + 0x44) & 0xFF;
	else if (channel == 1)
		data->shift.g = (data->shift.g + 0x44) & 0xFF;
	else
		data->shift.b = (data->shift.b + 0x44) & 0xFF;
}

void	draw_controls(t_data *data)
{
	static const char	*lines[] = {"Wheel: zoom  Arrows: move",
		"+/-: iterations  C/V/B: shift colour", "P: palette  J: live julia",
		"Tab: next fractal  R: reset", "H: hide help  Esc: quit", NULL};
	int					i;

	i = -1;
	while (lines[++i])
	{
		mlx_string_put(data->mlx, data->win, 11, 21 + i * 15, BLACK,
			(char *)lines[i]);
		mlx_string_put(data->mlx, data->win, 10, 20 + i * 15, WHITE,
			(char *)lines[i]);
	}
}
