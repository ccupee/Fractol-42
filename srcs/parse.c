/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:17:28 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/14 13:17:29 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static double	atoi_utils(const char *str)
{
	double	num2;

	num2 = 0;
	if (*str == '.')
	{
		while (*str)
			str++;
		str--;
		while (*str != '.')
		{
			num2 = num2 + *str - '0';
			num2 *= 0.1;
			str--;
		}
	}
	return (num2);
}

static double	atoi_double(const char *str)
{
	double	num1;
	double	num2;
	double	res;

	num1 = 0;
	res = 1;
	if (*str == '-')
	{
		res = -1;
		str++;
	}
	while ((*str != '.') && (*str))
	{
		num1 = num1 * 10 + *str - '0';
		str++;
	}
	num2 = atoi_utils(str);
	return (res * (num1 + num2));
}

static void	check_name(t_fractol *data, char *name)
{
	if (!ft_strcmp(name, "Julia"))
		data->type = 0;
	else if (!ft_strcmp(name, "Mandelbrot"))
		data->type = 1;
	else if (!ft_strcmp(name, "BurningShip"))
		data->type = 3;
	else
		error("ERROR: No such fractal\n\
			Correct names:\nJulia\nMandelbrot\nBurningShip\n");
}

void	check_arguments(t_fractol *data, int argc, char **argv)
{
	if (argc < 2)
		error("ERROR: Wrong number of arguments\n");
	else
	{
		check_name(data, argv[1]);
		if ((data->type == 1 || data->type == 3) && argc > 2)
			error("ERROR: Wrong number of arguments\n");
		if (data->type == 0)
		{
			if (argc != 4)
			{
				if (argc == 2)
					data->type = 2;
				else
					error("ERROR: Wrong number of arguments\n");
			}
			else
			{
				data->arg1 = atoi_double(argv[2]);
				data->arg2 = atoi_double(argv[3]);
			}
		}	
	}
}
