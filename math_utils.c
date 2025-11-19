/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 08:31:24 by ztoptas           #+#    #+#             */
/*   Updated: 2025/11/19 08:31:24 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_iter(t_complex z, t_complex c)
{
	int	iter;

	iter = 0;
	while (iter < MAX_ITER)
	{
		if ((z.re * z.re + z.im * z.im) > 4.0)
			return (iter);
		z = complex_square(z);
		z.re += c.re;
		z.im += c.im;
		iter++;
	}
	return (MAX_ITER);
}

t_complex	complex_square(t_complex z)
{
	t_complex	result;

	result.re = z.re * z.re - z.im * z.im;
	result.im = 2.0 * z.re * z.im;
	return (result);
}

int	mandelbrot_iter(t_complex c)
{
	t_complex	z;
	int			iter;

	z.re = 0.0;
	z.im = 0.0;
	iter = 0;
	while (iter < MAX_ITER)
	{
		if ((z.re * z.re + z.im * z.im) > 4.0)
			return (iter);
		z = complex_square(z);
		z.re += c.re;
		z.im += c.im;
		iter++;
	}
	return (MAX_ITER);
}
