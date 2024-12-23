/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:04:45 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/23 11:00:34 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_complex	julia(t_m *m, t_complex z, t_complex c)
{
	(void)c;
	return (complex_add(complex_multiply(z, z), m->c));
}

static t_complex	mandelbrot(t_m *m, t_complex z, t_complex c)
{
	(void)m;
	return (complex_add(complex_multiply(z, z), c));
}

static t_complex	mandelbrot_2(t_m *m, t_complex z, t_complex c)
{
	(void)m;
	return (complex_cos(complex_divide(z, c)));
}

// cos(z)+1/c
static t_complex	mandelbrot_3(t_m *m, t_complex z, t_complex c)
{
	t_complex	n;

	(void)m;
	n = complex_divide((t_complex){1, 0}, c);
	return (complex_add(complex_cos(z), n));
}

void	fractal_set(t_m *m, int fractal_num)
{
	if (fractal_num < 1 || 4 < fractal_num)
		return (terminate(m, "fractal num invalid"));
	m->fractal.scale = 4;
	m->fractal.origin.x = WINDOW_W / 2;
	m->fractal.origin.y = WINDOW_H / 2;
	if (fractal_num == 1)
	{
		m->c.r = -0.75;
		m->c.i = 0;
		m->fractal.iteration = julia;
	}
	if (fractal_num == 2)
	{
		m->fractal.iteration = mandelbrot;
		m->fractal.origin.x = 2 * (WINDOW_W / 3);
	}
	if (fractal_num == 3)
		m->fractal.iteration = mandelbrot_2;
	if (fractal_num == 4)
		m->fractal.iteration = mandelbrot_3;
}
