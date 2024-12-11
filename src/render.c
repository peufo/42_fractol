/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 22:51:48 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render(t_m *m)
{
	img_draw_square(
		m->img,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);
	view_draw_line_v(m->img, -1, 0x000000);
	view_draw_line_v(m->img, 0, 0x000000);
	view_draw_line_v(m->img, 1, 0x000000);
	view_draw_line_h(m->img, -1, 0x000000);
	view_draw_line_h(m->img, 0, 0x000000);
	view_draw_line_h(m->img, 1, 0x000000);
	mlx_put_image_to_window(m->mlx, m->win, m->img->data, 0, 0);
}