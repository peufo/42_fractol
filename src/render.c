/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/17 18:33:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define COLOR_A 0xD4781A
#define COLOR_B 0xAA3678

static int	get_color(t_complex z)
{
	double	magnitude;

	z = complex_divergence(z);
	magnitude = complex_magnitude(z);
	if (magnitude < 4)
		return (COLOR_A);
	return (COLOR_B);
}

int get_square(t_complex z)
{
	if (z.r < -1)
		return (0);
	if (z.r > 0)
		return 0;
	if (z.i > 1)
		return 0;
	if (z.i < 0)
		return 0;
	return 0xff0000; 
}

void	render(t_m *m)
{
	img_draw_square(
		m->img,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);

	view_draw(m, get_color);

	/*
	view_draw_line_v(m->img, -2, 0x000000);
	view_draw_line_v(m->img, -1, 0x000000);
	view_draw_line_v(m->img, 0, 0x00FF00);
	view_draw_line_v(m->img, 1, 0x000000);
	view_draw_line_v(m->img, 2, 0x000000);
	view_draw_line_h(m->img, -1.5, 0x000000);
	view_draw_line_h(m->img, -1, 0x000000);
	view_draw_line_h(m->img, 0, 0x00FF00);
	view_draw_line_h(m->img, 1, 0x000000);
	view_draw_line_h(m->img, 1.5, 0x000000);
	*/
	mlx_put_image_to_window(m->mlx, m->win, m->img->data, 0, 0);
}
