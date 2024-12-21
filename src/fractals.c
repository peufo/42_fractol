/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:04:45 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/21 01:00:36 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	julia(t_m *m, t_complex z)
{
	t_bound	bound;

	bound = complex_bounded(m, z, m->c);
	return (get_gradient(m, bound));
}

static int	mandelbrot(t_m *m, t_complex z)
{
	t_bound	bound;

	bound = complex_bounded(m, z, z);
	return (get_gradient(m, bound));
}

void	fractal_set(t_m *m, int fractal_num)
{
	if (fractal_num < 1 || 2 < fractal_num)
		return (terminate(m, "fractal num invalid"));
	if (fractal_num == 1)
	{
		m->c.r = -0.75;
		m->c.i = 0;
		m->fractal.get_color = julia;
		m->fractal.scale = 4;
		m->fractal.origin.x = WINDOW_W / 2;
		m->fractal.origin.y = WINDOW_H / 2;
	}
	if (fractal_num == 2)
	{
		m->fractal.get_color = mandelbrot;
		m->fractal.scale = 4;
		m->fractal.origin.x = 2 * (WINDOW_W / 3);
		m->fractal.origin.y = WINDOW_H / 2;
	}
}
