/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 07:30:20 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/18 07:35:10 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_pallete_r(t_data *data)
{
	data->pallete[8] += 0x440000;
	data->pallete[7] += 0x440000;
	data->pallete[6] += 0x440000;
	data->pallete[5] += 0x440000;
	data->pallete[4] += 0x440000;
	data->pallete[3] += 0x440000;
	data->pallete[2] += 0x440000;
	data->pallete[1] += 0x440000;
	data->pallete[0] += 0x440000;
	data->fill_color = data->pallete[data->fill_index];
}

void	change_pallete_g(t_data *data)
{
	data->pallete[8] += 0x004400;
	data->pallete[7] += 0x004400;
	data->pallete[6] += 0x004400;
	data->pallete[5] += 0x004400;
	data->pallete[4] += 0x004400;
	data->pallete[3] += 0x004400;
	data->pallete[2] += 0x004400;
	data->pallete[1] += 0x004400;
	data->pallete[0] += 0x004400;
	data->fill_color = data->pallete[data->fill_index];
}

void	change_pallete_b(t_data *data)
{
	data->pallete[8] += 0x000044;
	data->pallete[7] += 0x000044;
	data->pallete[6] += 0x000044;
	data->pallete[5] += 0x000044;
	data->pallete[4] += 0x000044;
	data->pallete[3] += 0x000044;
	data->pallete[2] += 0x000044;
	data->pallete[1] += 0x000044;
	data->pallete[0] += 0x000044;
	data->fill_color = data->pallete[data->fill_index];
}
