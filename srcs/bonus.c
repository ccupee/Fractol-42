/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:57:15 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/14 14:57:17 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	burning_ship(double x, double y)
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
		tmp.im = fabsl(2 * x * y);
		x = tmp.re + c.re;
		y = -tmp.im + c.im;
	}
	return (i);
}
