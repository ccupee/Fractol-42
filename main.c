#include "fractol.h"

static double	pow(double nbr, int pow)
{
	int	i;
	double	res;

	i = 0;
	res = nbr;
	while (++i <= pow)
		res *= nbr;
	return (res);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//mlx
void	win_init(t_fractol *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error("ERROR: Can\'t initialize window\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	//
}

void	my_mlx_pixel_put(t_fractol *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data_addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
//

//Julia arguments
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

double	atoi_double(const char *str)
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
//

//parsing
void	check_name(t_fractol *data, char *name)
{
	if (!ft_strcmp(name, "Julia"))
		data->type = 0;
	else if (!ft_strcmp(name, "Mandelbrot"))
		data->type = 1;
	else
		error("ERROR: No such fractal\n\
			Correct names:\nJulia\nMandelbrot\n");
}

void	check_arguments(t_fractol *data, int argc, char **argv)
{
	if (argc < 2)
		error("ERROR: Wrong number of arguments\n");
	else
	{
		check_name(data, argv[1]);
		if (data->type == 1 && argc > 2)
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
//

//
static t_complex	init_parameters(t_complex k, double a, double b)
{
	k.re = a;
	k.im = b;
	return (k);
}

void	init_fractal(t_fractol *data, t_complex k)
{
	data->color[0] = 3;
	data->color[1] = 9;
	data->color[2] = 7;
	data->x0 = -500;
	data->y0 = 500;
	if (data->type == 1)
		k = init_parameters(k, 0, 0);
	else if (data->type == 0)
		k = init_parameters(k, 0.367811, 0.367811);
	else
		k = init_parameters(k, data->arg1, data->arg2);
}
//


int	main(int argc, char **argv)
{
	t_fractol	*data;
	t_complex	k;

	data = (t_fractol *)malloc(sizeof(t_fractol));
	if (!data)
		error("ERROR: Problems with memory\n");
	win_init(data);
	check_arguments(data, argc, argv);
	//win_init(data);

	mlx_loop(data->mlx_ptr);
	return (0);
}