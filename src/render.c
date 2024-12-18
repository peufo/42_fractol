/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 21:54:08 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define COLOR_A 0xD4781A
#define COLOR_B 0xAA3678

static int	get_color(t_m *m, t_complex z)
{
	t_bound	bound;

	bound = complex_bounded(z, z);
	if (bound.magnitude < 4)
		return (m->colors.a);
	if (bound.magnitude < 6)
		return (m->colors.b);
	if (bound.magnitude < 8)
		return (m->colors.c);
	if (bound.magnitude < 10)
		return (m->colors.d);
	return (m->colors.e);
}

void	render(t_m *m)
{
	img_draw_square(
		m->img,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);
	view_draw(m, get_color);
	mlx_put_image_to_window(m->mlx, m->win, m->img->data, 0, 0);
}
