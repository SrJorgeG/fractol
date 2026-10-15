/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:00:00 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	const char	*msg;

	msg = "Usage: ./fractol mandelbrot\n"
		"       ./fractol julia <real> <imaginary>  (e.g. julia -0.8 0.156)\n"
		"       ./fractol bship\n";
	write(2, msg, ft_strlen(msg));
	cleanup(data, 1);
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
		data->j_user_real = ft_atod(av[2], 0);
		data->j_user_i = ft_atod(av[3], 0);
	}
	else if (ac == 2 && !ft_strncmp("bship", av[1], 6))
		data->frac_type = BSHIP;
	else
		usage_exit(data);
	reset_values(data);
}
