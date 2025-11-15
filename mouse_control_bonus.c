#include "fractol_bonus.h" // 3 func.
#include <stdio.h>

int mouse_zoom(int button, int x, int y, t_fractol *f)
{
    double zoom_factor;
    double mouse_re;
    double mouse_im;
    double re_range;
    double im_range;
    double zoom_level;

    if (button != 4 && button != 5)
        return (0);
    zoom_factor = (button == 4) ? 0.9 : 1.1;
    mouse_re = f->min_re + (f->max_re - f->min_re) * x / (double)WIDTH;
    mouse_im = f->min_im + (f->max_im - f->min_im) * y / (double)HEIGHT;
    re_range = (f->max_re - f->min_re) * zoom_factor;
    im_range = (f->max_im - f->min_im) * zoom_factor;
    f->min_re = mouse_re - re_range * x / (double)WIDTH;
    f->max_re = f->min_re + re_range;
    f->min_im = mouse_im - im_range * y / (double)HEIGHT;
    f->max_im = f->min_im + im_range;
    zoom_level = 4.0 / (f->max_re - f->min_re);
    f->max_iter = (int)(BASE_MAX_ITER / zoom_level);
    if (f->max_iter < 0)
        f->max_iter = 0;
    printf("Zoom: %.2fx | Max iterations: %d\n", zoom_level, f->max_iter);
    draw_fractal_threaded(f);
    return (0);
}

int key_move(int keycode, t_fractol *f)
{
    double shift;
    
    if (keycode == 99)  // C tuşu
    {
        f->color_scheme = (f->color_scheme + 1) % 4;
        draw_fractal_threaded(f);
        return (0);
    }
    
    if (keycode == 114)  // R tuşu - RESET
    {
        init_map_params(f);
        f->max_iter = BASE_MAX_ITER;
        f->color_scheme = 0;
        draw_fractal_threaded(f);
        return (0);
    }
    shift = (f->max_re - f->min_re) * 0.1;
    if (keycode == 65361)  // Sol ok
    {
        f->min_re -= shift;
        f->max_re -= shift;
    }
    else if (keycode == 65363)  // Sağ ok
    {
        f->min_re += shift;
        f->max_re += shift;
    }
    else if (keycode == 65362)  // Yukarı ok
    {
        f->min_im -= shift;
        f->max_im -= shift;
    }
    else if (keycode == 65364)  // Aşağı ok
    {
        f->min_im += shift;
        f->max_im += shift;
    }
    else
        return (0);
    draw_fractal_threaded(f);
    return (0);
}

int mouse_move_julia(int x, int y, t_fractol *f)
{
    if (ft_strncmp(f->fractal_name, "julia", 6) != 0)
        return (0);
    f->julia_c.re = (x - WIDTH / 2.0) / (WIDTH / 4.0);
    f->julia_c.im = (y - HEIGHT / 2.0) / (HEIGHT / 4.0);  
    draw_fractal_threaded(f);
    return (0);
}