/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 14:25:46 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	complex_magnitude(t_complex z)
{
	return (z.r * z.r + z.i * z.i);
}

static void	complex_bounded(t_bound *res, t_m *m, t_complex *z)
{
	res->i = 0;
	res->magnitude = 0;
	res->z = *z;
	while (res->i < MAX_ITERATION && res->magnitude < 4)
	{
		m->fractal.iteration(m, &(res->z), z);
		res->magnitude = complex_magnitude(res->z);
		res->i++;
	}
	return ;
}

static int	get_color(t_m *m, t_complex *z)
{
	t_bound	bound;

	complex_bounded(&bound, m, z);
	return (get_gradient(m, bound));
}

int	request_render(t_m *m)
{
	m->rendering_requested = 1;
	return (0);
}

int	render(t_m *m)
{
	if (!m->rendering_requested)
		return (0);
	m->rendering_requested = 0;
	view_draw(m, get_color);
	mlx_put_image_to_window(m->mlx, m->win, m->img.data, 0, 0);
	return (1);
}
