#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

#include <stddef.h>
#include "mlx.h"

#define WIDTH 600
#define HEIGHT 600
#define BASE_MAX_ITER 50

#define KEY_ESC     65307
#define KEY_LEFT    65361
#define KEY_UP      65362
#define KEY_RIGHT   65363
#define KEY_DOWN    65364
#define KEY_C       99

#define MOUSE_SCROLL_UP     4
#define MOUSE_SCROLL_DOWN   5


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


void init_map_params(t_fractol *f);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
double  ft_atof(const char *str);
void	ft_putstr(char *s);
int julia_iter(t_complex z, t_complex c, int max_iter);
int mandelbrot_iter(t_complex c, int max_iter);
t_complex complex_square(t_complex z);
int draw_fractal(t_fractol *f);
int mouse_zoom(int button, int x, int y, t_fractol *f);
int mouse_move_julia(int x, int y, t_fractol *f);
int key_move(int keycode, t_fractol *f);
int init_mlx(t_fractol *f);
int destroy_and_exit(t_fractol *f);
int is_esc(int keycode, t_fractol *f);
void mlx_hooks(t_fractol *f);

#endif