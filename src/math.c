/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:41:32 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/22 21:35:50 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	limit_sup(int v, int limit)
{
	if (v > limit)
		return (limit);
	return (v);
}

int	limit_inf(int v, int limit)
{
	if (v < limit)
		return (limit);
	return (v);
}

double	double_limit(double v, double limit)
{
	if (v > limit)
		return (limit);
	return (v);
}

t_complex	complex_sinh(t_complex z)
{
	return ((t_complex){
		.r = sinh(z.r) * cos(z.i),
		.i = cosh(z.r) * sin(z.i)
	});
}

t_complex	complex_cos(t_complex z)
{
	return ((t_complex){
		.r = cos(z.r) * cosh(z.i),
		.i = -(sin(z.r) * sinh(z.i))
	});
}
