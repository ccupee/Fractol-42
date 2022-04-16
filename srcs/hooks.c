/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:15:54 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/14 13:15:59 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	get_color(t_fractol *img)
{
	if (img->n == 0)
	{
		img->n = 1;
		img->color[0] = 5;
		img->color[1] = 14;
		img->color[2] = 4;
	}
	else if (img->n == 1)
	{
		img->n = 2;
		img->color[0] = 1;
		img->color[1] = 12;
		img->color[2] = 10;
	}
	else if (img->n == 2)
	{
		img->n = 0;
		img->color[0] = 3;
		img->color[1] = 9;
		img->color[2] = 7;
	}
}

int	ft_expose_hook(t_fractol *data)
{
	draw_fractal(data);
	return (0);
}

int	ft_close_window(int keycode, t_fractol *list)
{
	exit(0);
	(void)list;
	return (keycode);
}

int	ft_key_hook(int keycode, t_fractol *img)
{
	mlx_clear_window(img->mlx_ptr, img->win_ptr);
	if (keycode == KEY_ESC)
		ft_close_window(keycode, img);
	if (keycode == KEY_C)
		get_color(img);
	draw_fractal(img);
	return (keycode);
}

int	ft_mouse_hook(int keycode, int x, int y, t_fractol *img)
{
	mlx_clear_window(img->mlx_ptr, img->win_ptr);
	if (keycode == SCROLL_DOWN)
	{
		img->scale *= 1.2;
		x = 0;
		y = 0;
	}
	if (keycode == SCROLL_UP && img->scale > 0)
	{
		img->scale *= 0.8;
		x = 0;
		y = 0;
	}
	draw_fractal(img);
	return (keycode);
}
