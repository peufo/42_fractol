/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:04:45 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/23 14:09:21 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	julia(t_m *m, t_complex *z, t_complex *c)
{
	double	r;

	(void)c;
	r = (z->r * z->r) - (z->i * z->i) + m->c.r;
	z->i = 2 * (z->r * z->i) + m->c.i;
	z->r = r;
}

static void	mandelbrot(t_m *m, t_complex *z, t_complex *c)
{
	double	r;

	(void)m;
	r = (z->r * z->r) - (z->i * z->i) + c->r;
	z->i = 2 * (z->r * z->i) + c->i;
	z->r = r;
}

static void	mandelbrot_2(t_m *m, t_complex *z, t_complex *c)
{
	double	r;
	double	i;
	double	dividor;

	(void)m;
	dividor = (c->r * c->r) + (c->i * c->i);
	r = ((z->r * c->r) + (z->i * c->i)) / dividor;
	i = ((z->i * c->r) - (z->r * c->i)) / dividor;
	z->r = cos(r) * cosh(i);
	z->i = -(sin(r) * sinh(i));
}

void	fractal_set(t_m *m, int fractal_num)
{
	if (fractal_num < 1 || 3 < fractal_num)
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
}
