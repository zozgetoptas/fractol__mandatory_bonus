/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_fractal_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:30:54 by ztoptas           #+#    #+#             */
/*   Updated: 2025/11/19 08:30:54 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	get_rgb_by_scheme(int scheme, double t, int *rgb)
{
	if (scheme == 0)
	{
		rgb[0] = (int)(9 * t * 255) % 256;
		rgb[1] = (int)(15 * t * 255) % 256;
		rgb[2] = (int)(30 * t * 255) % 256;
	}
	else if (scheme == 1)
	{
		rgb[0] = (int)(8 * t * 255) % 256;
		rgb[1] = (int)(18 * t * 255) % 256;
		rgb[2] = (int)(25 * t * 255) % 256;
	}
	else if (scheme == 2)
	{
		rgb[0] = (int)(12 * t * 255) % 256;
		rgb[1] = (int)(20 * t * 255) % 256;
		rgb[2] = (int)(28 * t * 255) % 256;
	}
	else
	{
		rgb[0] = (int)(10 * t * 255) % 256;
		rgb[1] = (int)(16 * t * 255) % 256;
		rgb[2] = (int)(22 * t * 255) % 256;
	}
}

static int	get_color(int iter, int max_iter, int scheme)
{
	int		rgb[3];
	double	t;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	get_rgb_by_scheme(scheme, t, rgb);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
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
