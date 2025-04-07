/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:59:58 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 20:50:08 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char *av[])
{
	t_data	*data;

	data = NULL;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		error_exit(data);
	pre_init(data);
	if (ac == 2 && !ft_strncmp("mandelbrot", av[1], 10))
		data->frac_type = MANDELBROT;
	else if (ac == 4 && !ft_strncmp("julia", av[1], 6))
		data->frac_type = JULIA;
	else
		error_exit(data);
	init(data);
	draw(data);
	mlx_loop(data->mlx);
	return (0);
}
