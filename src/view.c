/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 12:48:09 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	view_init(t_m *m)
{
	m->view.scale = m->fractal.scale;
	m->view.origin = m->fractal.origin;
	view_update(m);
	render(m);
}

void	view_update(t_m *m)
{
	t_view	*view;
	int		i;

	view = &m->view;
	view->pixel_to_view = view->scale / m->img.pixels_per_line;
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

static void	view_predraw(t_m *m, int (*get_color)(t_m*, t_complex))
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
			color = get_color(m, z);
			img_draw_square(m,
				(t_dot){r.x * PREDRAW_RES, r.y * PREDRAW_RES},
				(t_dot){PREDRAW_RES, PREDRAW_RES},
				color);
			r.y++;
		}
		r.x++;
	}
}

void	view_draw(t_m *m, int (*get_color)(t_m*, t_complex))
{
	int		x;
	int		y;
	int		color;
	t_view	*view;

	view = &m->view;
	if (m->is_mode_predraw)
		return (view_predraw(m, get_color));
	x = 0;
	while (x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			color = get_color(m, (t_complex){view->x[x], view->y[y]});
			img_put_pixel(m, x, y, color);
			y++;
		}
		x++;
	}
}
