#include "fractol_bonus.h" // 3 func.

int	adaptive_max_iter(t_fractol *f)
{
	double	zoom_level;

	zoom_level = 4.0 / (f->max_re - f->min_re);
	return ((int)(100 + zoom_level * 50));
}

int	julia_iter(t_complex z, t_complex c, int max_iter)
{
	int	iter;

	iter = 0;
	while (iter < max_iter)
	{
		if ((z.re * z.re + z.im * z.im) > 4.0)
			return (iter);
		z = complex_square(z);
		z.re += c.re;
		z.im += c.im;
		iter++;
	}
	return (max_iter);
}

t_complex	complex_square(t_complex z)
{
	t_complex	result;

	result.re = z.re * z.re - z.im * z.im;
	result.im = 2.0 * z.re * z.im;
	return (result);
}

int	mandelbrot_iter(t_complex c, int max_iter)
{
	t_complex	z;
	int			iter;

	z.re = 0.0;
	z.im = 0.0;
	iter = 0;
	while (iter < max_iter)
	{
		if ((z.re * z.re + z.im * z.im) > 4.0)
			return (iter);
		z = complex_square(z);
		z.re += c.re;
		z.im += c.im;
		iter++;
	}
	return (max_iter);
}
