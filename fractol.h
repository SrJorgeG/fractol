/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:01:35 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 01:26:31 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define HEIGHT 1000
# define WIDTH 1000
# define MANDELBROT 1
# define JULIA 2

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>


typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	
} t_imgdata;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			frac_type;
	t_imgdata 	*img_data;
	int			pallete[9];
	double		inc_x;
	double		inc_y;
	double		quality;
	double		zoom;
	int			is_print;
	double		scale_x;
	double		scale_y;
	double		j_c_real;
	double		j_c_i;
	
} t_data;


int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	error_exit(t_data *data);
void	init(t_data *data);







#endif