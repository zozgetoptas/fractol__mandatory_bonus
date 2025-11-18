#include "fractol.h"
#include <stdlib.h>

int	init_mlx(t_fractol *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		return (0);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fractol");
	if (f->win == NULL)
	{
		mlx_destroy_display(f->mlx);
		return (0);
	}
	f->img.img_ptr = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->img.addr = mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
			&f->img.line_len, &f->img.endian);
	f->min_re = -2.0;
	f->max_re = 2.0;
	f->min_im = -2.0;
	f->max_im = 2.0;
	return (1);
}

int	destroy_and_exit(t_fractol *f)
{
	if (f->img.img_ptr)
		mlx_destroy_image(f->mlx, f->img.img_ptr);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
    {
        mlx_destroy_display(f->mlx);
        free(f->mlx);
    }
	exit(0);
}

int	is_esc(int keycode, t_fractol *f)
{
	if (keycode == KEY_ESC)
		destroy_and_exit(f);
	return (0);
}

void	mlx_hooks(t_fractol *f)
{
	mlx_key_hook(f->win, is_esc, f);
	mlx_hook(f->win, 17, 0, destroy_and_exit, f);
	mlx_mouse_hook(f->win, mouse_scroll, f);
}
