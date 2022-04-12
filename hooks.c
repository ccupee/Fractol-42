#include "fractol.h"

int	ft_expose_hook(t_fractol *data)
{
	draw_fractal(data);
	return (0);
}
