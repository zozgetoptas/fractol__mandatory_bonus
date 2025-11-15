#include "fractol.h" // 3 func
#include <unistd.h>
#include <stdlib.h>

static void	print_right_usage_and_exit(void)
{
	ft_putstr("right usage: ./fractol <frcl_name> [julia_re] [julia_im]\n");
	ft_putstr("available fractals:\n");
	ft_putstr("  - mandelbrot\n");
	ft_putstr("  - julia <C_re> <C_im>\n");
	exit(1);
}

static int	parse_arguments(int argc, char **argv, t_fractol *f)
{
	if (argc < 2)
		print_right_usage_and_exit();
	f->fractal_name = argv[1];
	if (ft_strncmp(f->fractal_name, "mandelbrot", 11) == 0)
		return (1);
	else if (ft_strncmp(f->fractal_name, "julia", 6) == 0)
	{
		if (argc < 4)
			print_right_usage_and_exit();
		f->julia_c.re = ft_atof(argv[2]);
		f->julia_c.im = ft_atof(argv[3]);
		return (1);
	}
	else
		print_right_usage_and_exit();
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (!parse_arguments(argc, argv, &f))
		return (1);
	if (!init_mlx(&f))
		return (1);
	mlx_hooks(&f);
	draw_fractal(&f);
	mlx_loop(f.mlx);
	return (0);
}
