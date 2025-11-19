/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:31:07 by ztoptas           #+#    #+#             */
/*   Updated: 2025/11/19 08:31:07 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include <stddef.h>
# include "mlx.h"

# define WIDTH 600
# define HEIGHT 600
# define BASE_MAX_ITER 50

# define KEY_ESC     65307
# define KEY_LEFT    65361
# define KEY_UP      65362
# define KEY_RIGHT   65363
# define KEY_DOWN    65364
# define KEY_C       99

# define MOUSE_SCROLL_UP     4
# define MOUSE_SCROLL_DOWN   5

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
	int			max_iter;
	int			color_scheme;
}	t_fractol;

void		init_map_params(t_fractol *f);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
double		ft_atof(const char *str);
void		ft_putstr(char *s);
int			julia_iter(t_complex z, t_complex c, int max_iter);
int			mandelbrot_iter(t_complex c, int max_iter);
t_complex	complex_square(t_complex z);
int			draw_fractal(t_fractol *f);
int			mouse_zoom(int button, int x, int y, t_fractol *f);
int			mouse_move_julia(int x, int y, t_fractol *f);
int			key_move(int keycode, t_fractol *f);
int			init_mlx(t_fractol *f);
int			destroy_and_exit(t_fractol *f);
int			is_esc(int keycode, t_fractol *f);
void		mlx_hooks(t_fractol *f);

#endif