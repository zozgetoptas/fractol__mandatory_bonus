/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:31:10 by ztoptas           #+#    #+#             */
/*   Updated: 2025/11/19 08:31:10 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stddef.h>
# include "mlx.h"

# define WIDTH 600
# define HEIGHT 600
# define MAX_ITER 100

# define KEY_ESC 65307

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_image		img;
	char		*fractal_name;
	double		min_re;
	double		max_re;
	double		min_im;
	double		max_im;
	t_complex	julia_c;
}	t_fractol;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
double		ft_atof(const char *str);
int			draw_fractal(t_fractol *f);
int			julia_iter(t_complex z, t_complex c);
t_complex	complex_square(t_complex z);
int			mandelbrot_iter(t_complex c);
int			init_mlx(t_fractol *f);
int			destroy_and_exit(t_fractol *f);
int			is_esc(int keycode, t_fractol *f);
void		mlx_hooks(t_fractol *f);
int			close_window(t_fractol *f);
int			mouse_scroll(int button, int x, int y, t_fractol *f);
void		ft_putstr(char *s);

#endif