#include "fractol_bonus.h"
#include <stdlib.h>

void	init_map_params(t_fractol *f)
{
	f->min_re = -2.0;
	f->max_re = 2.0;
	f->min_im = -2.0;
	f->max_im = 2.0;
	f->max_iter = BASE_MAX_ITER;
	f->color_scheme = 0;
}

int	init_mlx(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		return (0);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fractol");
	if (f->win == 0)
	{
		mlx_destroy_display(f->mlx);
		return (0);
	}
	f->img.img_ptr = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->img.addr = mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
			&f->img.line_len, &f->img.endian);
	init_map_params(f);
	return (1);
}

int	destroy_and_exit(t_fractol *f)
{
	if (f->img.img_ptr)
		mlx_destroy_image(f->mlx, f->img.img_ptr);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	exit(0);
}

int	is_esc(int keycode, t_fractol *f)
{
	if (keycode == 65307)
		destroy_and_exit(f);
	return (0);
}

void	mlx_hooks(t_fractol *f)
{
	mlx_key_hook(f->win, is_esc, f);
	mlx_hook(f->win, 2, 1L << 0, key_move, f);
	mlx_hook(f->win, 4, 1L << 2, mouse_zoom, f);
	mlx_hook(f->win, 6, 1L << 6, mouse_move_julia, f);
	mlx_hook(f->win, 17, 0, destroy_and_exit, f);
}
