#include "fractol_bonus.h" // 4 func.
#include <math.h>

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

static void	*draw_section(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	int				iter;
	t_complex		c;
	int				color;

	data = (t_thread_data *)arg;
	y = data->start_y - 1;
	while (++y < data->end_y)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c.re = data->f->min_re + (data->f->max_re - data->f->min_re) * x / WIDTH;
			c.im = data->f->min_im + (data->f->max_im - data->f->min_im) * y / HEIGHT;
			iter = 0;
			if (ft_strncmp(data->f->fractal_name, "mandelbrot", 11) == 0)
				iter = mandelbrot_iter(c, data->f->max_iter);
			else if (ft_strncmp(data->f->fractal_name, "julia", 6) == 0)
				iter = julia_iter(c, data->f->julia_c, data->f->max_iter);
			color = get_color(iter, data->f->max_iter, data->f->color_scheme);
			put_pixel(data->f, x, y, color);
		}
	}
	return (NULL);
}

int	draw_fractal_threaded(t_fractol *f)
{
	pthread_t       threads[NUM_THREADS];
	t_thread_data   data[NUM_THREADS];
	int             section_height;
	int             i;

	section_height = HEIGHT / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		data[i].f = f;
		data[i].start_y = i * section_height;
		data[i].end_y = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * section_height;
		pthread_create(&threads[i], NULL, draw_section, &data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img_ptr, 0, 0);
	return (0);
}
