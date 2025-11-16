#include "fractol_bonus.h" //  6 func
#include <stdio.h>

static void	calculate_zoom_range(int button, double *factor)
{
	if (button == 4)
		*factor = 0.9;
	else
		*factor = 1.1;
}

static void	update_zoom_bounds(t_fractol *f, double mouse_re, double mouse_im,
	double re_range, double im_range, int x, int y)
{
	f->min_re = mouse_re - re_range * x / (double)WIDTH;
	f->max_re = f->min_re + re_range;
	f->min_im = mouse_im - im_range * y / (double)HEIGHT;
	f->max_im = f->min_im + im_range;
}

int	mouse_zoom(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;
	double	re_range;
	double	im_range;

	if (button != 4 && button != 5)
		return (0);
	calculate_zoom_range(button, &zoom_factor);
	mouse_re = f->min_re + (f->max_re - f->min_re) * x / (double)WIDTH;
	mouse_im = f->min_im + (f->max_im - f->min_im) * y / (double)HEIGHT;
	re_range = (f->max_re - f->min_re) * zoom_factor;
	im_range = (f->max_im - f->min_im) * zoom_factor;
	update_zoom_bounds(f, mouse_re, mouse_im, re_range, im_range, x, y);
	printf("Zoom: %.2fx\n", 4.0 / (f->max_re - f->min_re));
	draw_fractal(f);
	return (0);
}

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
