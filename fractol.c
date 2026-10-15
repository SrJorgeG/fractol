/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 23:59:58 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	hook_caller(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hooks, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, good_exit, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, mouse_hooks, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, motion_hook, data);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	pre_init(data);
	parse(ac, av, data);
	init(data);
	hook_caller(data);
	draw(data);
	mlx_loop(data->mlx);
	return (0);
}
