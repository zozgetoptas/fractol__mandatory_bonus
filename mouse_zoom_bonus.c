#include "fractol_bonus.h"
#include <stdio.h>

int	mouse_zoom(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;
	double	re_range;
	double	im_range;

	if (button != 4 && button != 5)
		return (0);
	if (button == 4)
		zoom_factor = 0.9;
	else
		zoom_factor = 1.1;
	mouse_re = f->min_re + (f->max_re - f->min_re) * x / (double)WIDTH;
	mouse_im = f->min_im + (f->max_im - f->min_im) * y / (double)HEIGHT;
	re_range = (f->max_re - f->min_re) * zoom_factor;
	im_range = (f->max_im - f->min_im) * zoom_factor;
	f->min_re = mouse_re - re_range * x / (double)WIDTH;
	f->max_re = f->min_re + re_range;
	f->min_im = mouse_im - im_range * y / (double)HEIGHT;
	f->max_im = f->min_im + im_range;
	draw_fractal(f);
	return (0);
}
