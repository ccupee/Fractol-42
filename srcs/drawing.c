/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:15:01 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/14 13:15:06 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	my_mlx_pixel_put(t_fractol *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data_addr + (y * img->line_length + \
		x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	mandelbrot(double x, double y)
{
	t_complex	c;
	t_complex	tmp;
	int			i;

	i = -1;
	c.re = x;
	c.im = y;
	x = 0;
	y = 0;
	while (++i < 100 && (x * x + y * y <= 4))
	{
		tmp.re = x * x - y * y;
		tmp.im = 2 * x * y;
		x = tmp.re + c.re;
		y = tmp.im + c.im;
	}
	return (i);
}

static int	julia(t_fractol *data, double x, double y)
{
	t_complex	tmp;
	t_complex	k;
	int			i;

	i = -1;
	k.re = data->arg1;
	k.im = data->arg2;
	while (++i < 100 && (x * x + y * y < 4))
	{
		tmp.re = x * x - y * y;
		tmp.im = 2 * x * y;
		x = tmp.re + k.re;
		y = tmp.im + k.im;
	}
	return (i);
}

static int	choose_fractal(t_fractol *data, double x, double y)
{
	if (data->type == 1)
		return (mandelbrot(x, y));
	else if (data->type == 3)
		return (burning_ship(x, y));
	else
		return (julia(data, x, y));
}

void	draw_fractal(t_fractol *data)
{
	int		i;
	int		j;
	double	x;
	double	y;
	int		iter;

	i = 0;
	iter = 0;
	while (i++ < WIDTH)
	{
		j = 0;
		while (j++ < HEIGHT)
		{
			x = (data->x0 + i) / (double) data->scale;
			y = (data->y0 - j) / (double) data->scale;
			iter = choose_fractal(data, x, y);
			data->final_color = ((255 - iter * data->color[0]) << 16) \
				+ ((255 - iter * data->color[1]) << 8) + \
					(255 - iter * data->color[2]);
			my_mlx_pixel_put(data, i, j, data->final_color);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image, 0, 0);
}
