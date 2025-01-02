/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/02 15:59:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
