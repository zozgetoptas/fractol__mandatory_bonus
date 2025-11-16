#include "fractol_bonus.h"

static void	move_view(int keycode, t_fractol *f, double shift)
{
	if (keycode == 65361)
	{
		f->min_re -= shift;
		f->max_re -= shift;
	}
	else if (keycode == 65363)
	{
		f->min_re += shift;
		f->max_re += shift;
	}
	else if (keycode == 65362)
	{
		f->min_im -= shift;
		f->max_im -= shift;
	}
	else if (keycode == 65364)
	{
		f->min_im += shift;
		f->max_im += shift;
	}
	else if (keycode == 99)
	{
		f->color_scheme = (f->color_scheme + 1) % 4;
	}
}

int	key_move(int keycode, t_fractol *f)
{
	double	shift;

	shift = (f->max_re - f->min_re) * 0.1;
	move_view(keycode, f, shift);
	if (keycode >= 65361 && keycode <= 65364)
		draw_fractal(f);
	else if (keycode == 99)
		draw_fractal(f);
	return (0);
}

int	mouse_move_julia(int x, int y, t_fractol *f)
{
	if (ft_strncmp(f->fractal_name, "julia", 6) != 0)
		return (0);
	f->julia_c.re = (x - WIDTH / 2.0) / (WIDTH / 4.0);
	f->julia_c.im = (y - HEIGHT / 2.0) / (HEIGHT / 4.0);
	draw_fractal(f);
	return (0);
}
