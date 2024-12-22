/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:27:45 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/22 23:30:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	complex_add(t_complex a, t_complex b)
{
	return ((t_complex){.r = a.r + b.r, .i = a.i + b.i});
}

t_complex	complex_multiply(t_complex a, t_complex b)
{
	return ((t_complex){
		.r = (a.r * b.r) - (a.i * b.i),
		.i = (a.r * b.i) + (a.i * b.r)
	});
}

t_complex	complex_divide(t_complex a, t_complex b)
{
	double	r;
	double	i;
	double	dividor;

	dividor = (b.r * b.r) + (b.i * b.i);
	r = ((a.r * b.r) + (a.i * b.i)) / dividor;
	i = ((a.i * b.r) - (a.r * b.i)) / dividor;
	return ((t_complex){r, i});
}

double	complex_magnitude(t_complex z)
{
	return (z.r * z.r + z.i * z.i);
}

t_bound	complex_bounded(t_m *m, t_complex z)
{
	t_bound	res;

	res.i = 0;
	res.magnitude = 0;
	res.z = z;
	while (res.i < MAX_ITERATION && res.magnitude < 4)
	{
		res.z = m->fractal.iteration(m, res.z, z);
		res.magnitude = complex_magnitude(res.z);
		res.i++;
	}
	return (res);
}
