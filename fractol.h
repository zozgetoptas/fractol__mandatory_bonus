#ifndef FRACTOL_H
# define FRACTOL_H

#include <stddef.h>
#include "mlx.h"

#define WIDTH 600
#define HEIGHT 600
#define MAX_ITER 100

// mendelbrot
// z(n+1) = z(n)² + c
/* Her bir pikselin kümenin bir parçası olup olmadığını test etmek için,
z0 başlangıç değeri sıfır (0) olarak sabit tutulur.
Formüldeki c sabiti ise, test edilen pikselin karmaşık düzlemdeki koordinatlarını temsil eder
ve bu değer pikselden piksele değişir.
*/

// julia
// z(n+1) = z(n)² + c
/* burada, formüldeki c sabiti, tüm fraktal için dışarıdan belirlenen sabit bir parametre
olarak kullanılır ve fraktalın şeklini belirler.
İterasyonun başlangıç değeri olan z0 ise,
test edilen pikselin karmaşık düzlemdeki koordinatlarını temsil eder ve
bu değer pikselden piksele değişir.
*/

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
}               t_fractol;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
double  ft_atof(const char *str);
int draw_fractal(t_fractol *f);
int julia_iter(t_complex z, t_complex c);
t_complex complex_square(t_complex z);
int mandelbrot_iter(t_complex c);
int init_mlx(t_fractol *f);
int destroy_and_exit(t_fractol *f);
int is_esc(int keycode, t_fractol *f);
void mlx_hooks(t_fractol *f);
int     close_window(t_fractol *f);
int mouse_scroll(int button, int x, int y, t_fractol *f);
void	ft_putstr(char *s);

#endif