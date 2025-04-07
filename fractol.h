/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:01:35 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 21:37:06 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define HEIGHT 600
# define WIDTH 600
# define MANDELBROT 1
# define JULIA 2
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define QUALITY 42

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_imgdata;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_imgdata	*img_data;
	int			frac_type;
	int			pallete[9];
	double		inc_x;
	double		inc_y;
	double		quality;
	double		zoom;
	int			is_print;
	int			fill_color;
	int			fill_index;
	double		scale_x;
	double		scale_y;
	double		j_c_real;
	double		j_c_i;
}	t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// AUX FUNCTIONS

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

// INIT & ERROR

void	error_exit(t_data *data);
void	pre_init(t_data *data);
void	init(t_data *data);

// DRAW 

t_coord	iter_mandelbrot(t_coord z, t_coord c);
int	calc_iterations(t_data *data, t_coord z, t_coord c, t_coord (*iterate)(t_coord, t_coord));
double	re_scale(int num, double zoom, double inc, int scale);
void	draw(t_data *data);

// COLOR

void	set_pixel_color(t_imgdata *img_data, int x, int y, int color);
int		calc_gradient(int num_iter, int max_iter);
void	init_pallete(t_data *data);
int	smooth_color(double smooth_iter, double max_iter, t_data *data);

#endif