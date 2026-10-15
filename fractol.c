/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:59:58 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/19 02:58:33 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>

static double	ft_atod(const char *str, int *valid)
{
	double	nbr;
	double	div;
	double	sign;
	int		digits;

	digits = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	sign = 1.0;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1.0;
	nbr = 0.0;
	while (*str >= '0' && *str <= '9' && ++digits)
		nbr = nbr * 10 + (*(str++) - '0');
	div = 1.0;
	if (*str == '.' || *str == ',')
		while (*(++str) >= '0' && *str <= '9' && ++digits)
			nbr += (*str - '0') / (div *= 10.0);
	if (valid)
		*valid = (digits != 0 && *str == '\0');
	return (nbr * sign);
}

static int	isnum(char *str)
{
	int	valid;

	valid = 0;
	ft_atod(str, &valid);
	return (valid);
}

static void	usage_exit(t_data *data)
{
	write(2, "Usage: ./fractol mandelbrot\n"
		"       ./fractol julia <real> <imaginary>  (e.g. julia -0.8 0.156)\n"
		"       ./fractol bship\n", 118);
	error_exit(data);
}

void	parse(int ac, char *av[], t_data *data)
{
	if (ac == 2 && !ft_strncmp("mandelbrot", av[1], 11))
		data->frac_type = MANDELBROT;
	else if (ac == 4 && !ft_strncmp("julia", av[1], 6))
	{
		data->frac_type = JULIA;
		if (!isnum(av[2]) || !isnum(av[3]))
			usage_exit(data);
		data->j_c_real = ft_atod(av[2], 0);
		data->j_c_i = ft_atod(av[3], 0);
	}
	else if (ac == 2 && !ft_strncmp("bship", av[1], 6))
		data->frac_type = BSHIP;
	else
		usage_exit(data);
}

void	hook_caller(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hooks, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, (good_exit), data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, mouse_hooks, data);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = NULL;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		error_exit(data);
	pre_init(data);
	parse(ac, av, data);
	init(data);
	hook_caller(data);
	draw(data);
	mlx_loop(data->mlx);
	return (0);
}
