/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:01:35 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/07 19:25:07 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define HEIGHT 1000
# define WIDTH 1000
# define MANDELBROT 1
# define JULIA 2
# define WHITE 0xFFFFFF
# define BLACK 0x000000

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_coord
{
	double	x;
	double	y;
} t_coord;

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
	t_imgdata 	*img_data;
	int			frac_type;
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

t_coord	iter_mandelbrot(t_coord *z, t_coord *c);
int		calc_iterations(t_data *data, t_coord *z, t_coord *c);
double	re_scale(int num, double zoom, double inc, int scale);
void	draw(t_data *data);

// COLOR

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

void	set_pixel_color(t_imgdata *img_data, int x, int y, int color);
int		calc_gradient(int num_iter, int max_iter);






#endif