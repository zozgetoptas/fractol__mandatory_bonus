#include "fractol.h"

static int	get_color(int iter, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	t = (double)iter / max_iter;
	if (iter == max_iter)
		return (0x000000);
	r = (int)(9 * t * 255) % 256;
	g = (int)(15 * t * 255) % 256;
	b = (int)(30 * t * 255) % 256;
	return ((r << 16) | (g << 8) | b);
}

static void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	dst = f->img.addr + (y * f->img.line_len + x * (f->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	draw_fractal(t_fractol *f)
{
	int			x;
	int			y;
	int			iter;
	int			final_color;
	t_complex	c;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c.re = f->min_re + (f->max_re - f->min_re) * x / WIDTH;
			c.im = f->min_im + (f->max_im - f->min_im) * y / HEIGHT;
			iter = 0;
			if (ft_strncmp(f->fractal_name, "mandelbrot", 11) == 0)
				iter = mandelbrot_iter(c);
			else if (ft_strncmp(f->fractal_name, "julia", 6) == 0)
				iter = julia_iter(c, f->julia_c);
			final_color = get_color(iter, MAX_ITER);
			put_pixel(f, x, y, final_color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
	return (0);
}

int	mouse_scroll(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;
	double	center_re;
	double	center_im;
	double	width;
	double	height;
	double	min_width;

	(void)x;
	(void)y;
	if (button != 4 && button != 5)
		return (0);
	center_re = (f->min_re + f->max_re) / 2.0;
	center_im = (f->min_im + f->max_im) / 2.0;
	if (button == 4)
		zoom_factor = 0.8;
	else
		zoom_factor = 1.25;
	width = (f->max_re - f->min_re) * zoom_factor;
	height = (f->max_im - f->min_im) * zoom_factor;
	min_width = 1e-10;
	if (width < min_width)
		width = min_width;
	if (height < min_width)
		height = min_width;
	f->min_re = center_re - width / 2.0;
	f->max_re = center_re + width / 2.0;
	f->min_im = center_im - height / 2.0;
	f->max_im = center_im + height / 2.0;
	draw_fractal(f);
	return (0);
}
