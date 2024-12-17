/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:27:45 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/17 12:45:16 by jvoisard         ###   ########.fr       */
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

double	complex_magnitude(t_complex z)
{
	return (z.r * z.r + z.i * z.i);
}

t_complex	iteration_julia(t_complex z)
{
	t_complex	res;

	res = complex_multiply(z, z);
	res.r -= 0.5;
	return (res);
}

int	complex_is_divergent(t_complex z)
{
	int			i;
	t_complex	tmp;

	i = 0;
	while (i < MAX_ITERATION && complex_magnitude(z) < 5)
	{
		tmp = iteration_julia(z);
		z = tmp;
		i++;
	}
	return (complex_magnitude(z) < 5);
}
