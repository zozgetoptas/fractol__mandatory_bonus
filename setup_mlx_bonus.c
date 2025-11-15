#include "fractol_bonus.h"
#include <stdlib.h>

void init_map_params(t_fractol *f)
{   
    f->min_re = -2.0;
    f->max_re = 2.0;
    f->min_im = -2.0;
    f->max_im = 2.0;
}

int init_mlx(t_fractol *f)
{
    f->mlx = mlx_init(); // x11 sunucusuyla baglanti kurar, basariliysa 1 degilse 0 dondurur
    if (!f->mlx)
        return (0);
    f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "fractol"); // pencere ayarlaniyor, basligi fractol
    if (f->win == 0)
    {
        mlx_destroy_display(f->mlx);
        return (0);
    }
    f->img.img_ptr = mlx_new_image(f->mlx, WIDTH, HEIGHT); // canvasi olusturur
    f->img.addr = mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
	                                    &f->img.line_len, &f->img.endian);
    init_map_params(f);
    return (1);
}

int destroy_and_exit(t_fractol *f)
{
    if (f->img.img_ptr)
        mlx_destroy_image(f->mlx, f->img.img_ptr);
    // Pencereyi temizle
    if (f->win)
        mlx_destroy_window(f->mlx, f->win);
    // MLX bağlantısını temizle (bazı MLX versiyonlarında gereklidir)
    // mlx_destroy_display(f->mlx); 
    exit(0);
}

int is_esc(int keycode, t_fractol *f)
{
    if (keycode == 65307) 
        destroy_and_exit(f);
    return (0);
}

void mlx_hooks(t_fractol *f)
{
    mlx_key_hook(f->win, is_esc, f);                    // ESC tuşu
    mlx_hook(f->win, 2, 1L<<0, key_move, f);           // Klavye basma (ok tuşları)
    mlx_hook(f->win, 4, 1L<<2, mouse_zoom, f);         // Mouse button press (scroll)
    mlx_hook(f->win, 6, 1L<<6, mouse_move_julia, f);   // Mouse move (Julia için)
    mlx_hook(f->win, 17, 0, destroy_and_exit, f);      // Pencere kapatma
}

