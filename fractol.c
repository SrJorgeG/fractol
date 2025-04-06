/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:59:58 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 01:44:33 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char *av[])
{
	t_data	*data = NULL;

	init(data);
	if (ac == 2 && !ft_strncmp("mandelbrot", av[1], 10))
	{
		data->frac_type = MANDELBROT;
	} 
	else if (ac == 4 && !ft_strncmp("julia", av[1], 6))
	{
		data->frac_type = JULIA;
	} 
	else
		error_exit(data);
	mlx_loop(data->mlx);
	return 0;
}