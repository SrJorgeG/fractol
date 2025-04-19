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
#include <stdbool.h>

double	ft_atod(const char *str, int *valid)
{
	double			nbr;
	double			part;
	double			sign;
	int				valid_nums;

	valid_nums = 0;
	while (*str == ' ' || *str == '\f' || *str == '\t'
		|| *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	sign = 1.0;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1.0;
	nbr = 0.0;
	while (*str >= '0' && *str <= '9' && ++valid_nums)
		nbr = nbr * 10 + (*(str++) - '0');
	if (*str == '.' || *str == ',')
	{
		while (*(++str) >= '0' && *str <= '9' && ++valid_nums)
			part = 0.0;
		while (*(--str) >= '0' && *str <= '9')
			part = (part + (*str - '0')) / 10.0;
		nbr += part;
	}
	return (valid && (*valid = valid_nums != 0), nbr * sign);
}

int	isnum(char *str)
{
	int	i;

	i = 0;
	ft_atod(str, &i);
	if (!i)
		return (0);
	return (1);
}

void	parse(int ac, char *av[], t_data *data)
{
	if (ac == 2 && !ft_strncmp("mandelbrot", av[1], 10))
		data->frac_type = MANDELBROT;
	else if (ac == 4 && !ft_strncmp("julia", av[1], 6))
	{
		data->frac_type = JULIA;
		if (!isnum(av[2]) || !isnum(av[3]))
			error_exit(data);
		data->j_c_real = ft_atod(av[2], 0);
		data->j_c_i = ft_atod(av[3], 0);
	}
	else if (ac == 2 && !ft_strncmp("bship", av[1], 10))
		data->frac_type = BSHIP;
	else
		error_exit(data);
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
