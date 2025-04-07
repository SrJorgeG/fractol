/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:46:40 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 19:24:25 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_pixel_color(t_imgdata *img_data, int x, int y, int color)
{
	int	offset;
	
	offset = (y * img_data->line_length) + (x * (img_data->bpp / 8));
	*(unsigned int *)(img_data->addr + offset) = color;
}

int	calc_gradient(int num_iter, int max_iter)
{
	double	factor;
	t_color	fade;

	factor = num_iter / max_iter;
	fade.r = ((BLACK >> 16 & 0xFF) + ((WHITE >> 16 & 0xFF)
				- (BLACK >> 16 & 0xFF)) * factor);
	fade.g = ((BLACK >> 8 & 0xFF) + ((WHITE >> 8 & 0xFF)
				- (BLACK >> 8 & 0xFF)) * factor);
	fade.b = ((BLACK & 0xFF) + ((WHITE & 0xFF)
				- (BLACK & 0xFF)) * factor);
	return ((fade.r << 16) | (fade.g << 8) | fade.b);
}
