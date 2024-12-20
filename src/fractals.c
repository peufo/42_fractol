/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:04:45 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 12:44:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	julia(t_m *m, t_complex z)
{
	t_bound	bound;

	bound = complex_bounded(m, z, (t_complex){-0.75, 0});
	return (get_gradient(m, bound));
}

static int	mandelbrot(t_m *m, t_complex z)
{
	t_bound	bound;

	bound = complex_bounded(m, z, z);
	return (get_gradient(m, bound));
}

void	fractal_set(t_m *m, int fractal_index)
{
	if (fractal_index < 0 || fractal_index > 1)
		return (terminate(m, "fractal index invalid"));
	if (fractal_index == 0)
	{
		m->fractal.get_color = julia;
		m->fractal.scale = 4;
		m->fractal.origin.x = WINDOW_W / 2;
		m->fractal.origin.y = WINDOW_H / 2;
	}
	if (fractal_index == 1)
	{
		m->fractal.get_color = mandelbrot;
		m->fractal.scale = 4;
		m->fractal.origin.x = 2 * (WINDOW_W / 3);
		m->fractal.origin.y = WINDOW_H / 2;
	}
}
