/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 00:01:35 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:00:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define HEIGHT 600
# define WIDTH 600
# define MANDELBROT 0
# define JULIA 1
# define BSHIP 2
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define QUALITY 100.0
# define MAX_ITER 2000
# define NTHREADS 8
# define VIVID 0
# define GREY 1

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <X11/X.h>
# include <X11/keysym.h>

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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_imgdata	*img_data;
	int			frac_type;
	int			pallete[9];
	int			palette_mode;
	t_color		shift;
	double		inc_x;
	double		inc_y;
	double		quality;
	int			max_iter;
	double		zoom;
	int			fill_index;
	double		scale_x;
	double		scale_y;
	double		j_c_real;
	double		j_c_i;
	double		j_user_real;
	double		j_user_i;
	int			julia_live;
	int			show_help;
}	t_data;

typedef struct s_thread
{
	t_data	*data;
	int		id;
}	t_thread;

// AUX FUNCTIONS

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
double	re_scale(int num, double zoom, double inc, double scale);

// PARSE

void	parse(int ac, char *av[], t_data *data);

// INIT & CLEANUP

void	cleanup(t_data *data, int code);
void	pre_init(t_data *data);
void	init(t_data *data);
void	reset_values(t_data *data);

// DRAW

double	compute_iterations(t_coord variable, t_coord constant, t_data *data);
void	draw(t_data *data);

// COLOR

int		pixel_color(double smooth_iter, t_data *data);
void	set_pixel_color(t_imgdata *img_data, int x, int y, int color);

// HOOKS

int		good_exit(t_data *data);
int		mouse_hooks(int button, int x, int y, t_data *data);
int		motion_hook(int x, int y, t_data *data);
int		key_hooks(int keysym, t_data *data);

// HOOK UTILS

void	init_pallete(t_data *data);
void	shift_color(t_data *data, int channel);
void	draw_controls(t_data *data);

#endif
