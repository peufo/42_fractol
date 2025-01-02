/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/02 16:00:11 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	view_init(t_m *m)
{
	m->view.scale = m->fractal.scale;
	m->view.origin = m->fractal.origin;
	view_update(m);
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
	request_render(m);
}

static void	view_draw_low_res(t_m *m, int (*get_color)(t_m*, t_complex*))
{
	t_dot		r;
	t_dot		v;
	t_complex	z;
	int			color;

	r.x = 0;
	while (r.x < WINDOW_W / LOW_RES)
	{
		r.y = 0;
		while (r.y < WINDOW_H / LOW_RES)
		{
			v.x = r.x * LOW_RES + LOW_RES / 2;
			v.y = r.y * LOW_RES + LOW_RES / 2;
			z.r = m->view.x[v.x];
			z.i = m->view.y[v.y];
			color = get_color(m, &z);
			img_draw_square(m,
				(t_dot){r.x * LOW_RES, r.y * LOW_RES},
				(t_dot){LOW_RES, LOW_RES},
				color);
			r.y++;
		}
		r.x++;
	}
}

void	view_draw(t_m *m, int (*get_color)(t_m*, t_complex*))
{
	int			x;
	int			y;
	int			color;
	t_view		*view;
	t_complex	z;

	view = &m->view;
	if (m->is_low_res)
		return (view_draw_low_res(m, get_color));
	x = 0;
	while (x < WINDOW_W)
	{
		z.r = view->x[x];
		y = 0;
		while (y < WINDOW_H)
		{
			z.i = view->y[y];
			color = get_color(m, &z);
			img_put_pixel(m, x, y, color);
			y++;
		}
		x++;
	}
}
