/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:57:24 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(t_m *m, t_complex z)
{
	t_bound	bound;

	bound = complex_bounded(m, z, z);
	return (get_gradient(m, bound));
}

void	render(t_m *m)
{
	img_draw_square(
		m,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);
	view_draw(m, get_color);
	mlx_put_image_to_window(m->mlx, m->win, m->img.data, 0, 0);
}
