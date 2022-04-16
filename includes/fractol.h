/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:18:52 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/14 13:18:58 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include "../ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH			1000
# define HEIGHT			1000
# define KEY_ESC		53
# define KEY_CROSS		17
# define KEY_C			8
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define MASK_CROSS		131072L

typedef struct s_fractol
{
	void	*win_ptr;
	void	*mlx_ptr;
	void	*image;
	char	*data_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		type;
	int		color[3];
	int		final_color;
	int		n;
	double	scale;
	double	arg1;
	double	arg2;
	double	x0;
	double	y0;
}				t_fractol;

typedef struct s_complex
{
	double	re;
	double	im;
}				t_complex;

void	check_arguments(t_fractol *data, int argc, char **argv);

void	error(char *str);

void	draw_fractal(t_fractol *data);

int		ft_expose_hook(t_fractol *data);

void	init_fractal(t_fractol *data, t_complex *k);

void	win_init(t_fractol *data);

int		ft_expose_hook(t_fractol *data);

int		ft_close_window(int keycode, t_fractol *list);

int		ft_key_hook(int keycode, t_fractol *img);

int		ft_mouse_hook(int keycode, int x, int y, t_fractol *img);

int		burning_ship(double x, double y);

#endif
