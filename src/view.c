/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:53:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	view_init(t_m *m)
{
	m->view.scale = SCALE;
	m->view.origin.x = WINDOW_W / 2;
	m->view.origin.y = WINDOW_H / 2;
	view_update(m);
}

void	view_update(t_m *m)
{
	t_view	*view;
	int		i;

	view = &m->view;
	view->pixel_to_view = view->scale / m->img->pixels_per_line;
	i = 0;
	while (i < WINDOW_W)
	{
		view->x[i] = (i - view->origin.x) * view->pixel_to_view;
		i++;
	}
	i = 0;
	while (i < WINDOW_H)
	{
		view->y[i] = -(i - view->origin.y) * view->pixel_to_view;
		i++;
	}
}

static void	view_predraw(t_m *m, int (*draw)(t_m*, t_complex))
{
	t_dot		r;
	t_dot		v;
	t_complex	z;
	int			color;

	r.x = 0;
	while (r.x < WINDOW_W / PREDRAW_RES)
	{
		r.y = 0;
		while (r.y < WINDOW_H / PREDRAW_RES)
		{
			v.x = r.x * PREDRAW_RES + PREDRAW_RES / 2;
			v.y = r.y * PREDRAW_RES + PREDRAW_RES / 2;
			z.r = m->view.x[v.x];
			z.i = m->view.y[v.y];
			color = draw(m, z);
			img_draw_square(m,
				(t_dot){r.x * PREDRAW_RES, r.y * PREDRAW_RES},
				(t_dot){PREDRAW_RES, PREDRAW_RES},
				color);
			r.y++;
		}
		r.x++;
	}
}

void	view_draw(t_m *m, int (*draw)(t_m*, t_complex))
{
	int		x;
	int		y;
	int		color;
	t_view	*view;

	view = &m->view;
	if (m->is_mode_predraw)
		return (view_predraw(m, draw));
	x = 0;
	while (x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			color = draw(m, (t_complex){view->x[x], view->y[y]});
			img_put_pixel(m, x, y, color);
			y++;
		}
		x++;
	}
}
