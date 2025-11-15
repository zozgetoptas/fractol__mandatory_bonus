#ifndef FRACTOL_H
# define FRACTOL_H

#include <stddef.h>
#include <pthread.h>
#include "mlx.h"

#define WIDTH 600
#define HEIGHT 600
#define BASE_MAX_ITER 256

typedef struct s_complex
{
	double  re;
	double  im;
}               t_complex;

typedef struct s_image // bellek tabanli goruntu sistemini yonetir
{
	void    *img_ptr;
	char    *addr; // pixel verisinin bellek adresi
	int     bpp;    // bits per pixel
	int     line_len; // byte olarak satır uzunlugu
	int     endian; //  byte order (little/big endian)
}               t_image;

typedef struct s_fractol
{
	void        *mlx;       // mlx_init() sonucu, baglanti handlei
	void        *win;       // mlx_new_window() sonucu, pencere handlei
	t_image       img;        // görüntü verileri, buffer
	char        *fractal_name;
	double      min_re; // sol
	double      max_re; // sağ
	double      min_im; // alt
	double      max_im; // üst
	t_complex   julia_c; // c = julia_c.re + julia_c.im·i
	int         max_iter; // dinamik
	int         color_scheme; // Renk paleti (0, 1, 2, ...)
}               t_fractol;


#define NUM_THREADS 4  // Thread sayısı

typedef struct s_thread_data
{
	t_fractol   *f;
	int         start_y;
	int         end_y;
}   t_thread_data;

int adaptive_max_iter(t_fractol *f);
void init_map_params(t_fractol *f);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
double  ft_atof(const char *str);
void	ft_putstr(char *s);
int julia_iter(t_complex z, t_complex c, int max_iter);
int mandelbrot_iter(t_complex c, int max_iter);
t_complex complex_square(t_complex z);
int mouse_zoom(int button, int x, int y, t_fractol *f);
int mouse_move_julia(int x, int y, t_fractol *f);
int key_move(int keycode, t_fractol *f);
int draw_fractal_threaded(t_fractol *f);
int init_mlx(t_fractol *f);
int destroy_and_exit(t_fractol *f);
int is_esc(int keycode, t_fractol *f);
void mlx_hooks(t_fractol *f);

#endif