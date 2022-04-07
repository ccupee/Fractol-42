#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include "ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>

# define WIDTH 1000
# define HEIGHT 1000

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

#endif