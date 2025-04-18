/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:59:58 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/18 07:06:13 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atod(const char *str)
{
	double			nbr;
	double			part;
	double			sign;

	while (*str == ' ' || *str == '\f' || *str == '\t'
		|| *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1.0 ;
	else
		sign = 1.0;
	if (*str == '-' || *str == '+')
		str++;
	nbr = 0.0;
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*(str++) - '0');
	if (*str == '.' || *str == ',')
	{
		while (*(++str) >= '0' && *str <= '9')
			part = 0.0;
		while (*(--str) >= '0' && *str <= '9')
			part = (part + (*str - '0')) / 10.0;
		nbr += part;
	}
	return (nbr * sign);
}

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
	{
		data->frac_type = JULIA;
		data->j_c_real = ft_atod(av[2]);
		data->j_c_i = ft_atod(av[3]);
	}
	else if (ac == 2 && !ft_strncmp("bship", av[1], 10))
		data->frac_type = BSHIP;
	else
		error_exit(data);
	init(data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hooks, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, (good_exit), data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, mouse_hooks, data);
	draw(data);
	mlx_loop(data->mlx);
	return (0);
}
