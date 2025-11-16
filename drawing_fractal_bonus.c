#include "fractol_bonus.h"

static int	get_color(int iter, int max_iter, int scheme)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	if (scheme == 0)
	{
		r = (int)(9 * t * 255) % 256;
		g = (int)(15 * t * 255) % 256;
		b = (int)(30 * t * 255) % 256;
	}
	else if (scheme == 1)
	{
		// Parlak rainbow palette
		r = (int)(8 * t * 255) % 256;
		g = (int)(18 * t * 255) % 256;
		b = (int)(25 * t * 255) % 256;
	}
	else if (scheme == 2)
	{
		// Deniz-Okyanus palette (cyan-blue-purple)
		r = (int)(12 * t * 255) % 256;
		g = (int)(20 * t * 255) % 256;
		b = (int)(28 * t * 255) % 256;
	}
	else
	{
		// Ateş-Güneş palette (orange-yellow-red)
		r = (int)(10 * t * 255) % 256;
		g = (int)(16 * t * 255) % 256;
		b = (int)(22 * t * 255) % 256;
	}
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
				iter = mandelbrot_iter(c, BASE_MAX_ITER);
			else if (ft_strncmp(f->fractal_name, "julia", 6) == 0)
				iter = julia_iter(c, f->julia_c, BASE_MAX_ITER);
			final_color = get_color(iter, BASE_MAX_ITER, f->color_scheme);
			put_pixel(f, x, y, final_color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
	return (0);
}
