/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 22:42:42 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_view	*view_create(t_image *img)
{
	t_view	*view;

	view = malloc(sizeof(*view));
	if (!view)
		return (terminate("Malloc failed"), NULL);
	view->scale = SCALE;
	view->origin.x = WINDOW_W / 2;
	view->origin.y = WINDOW_H / 2;
	img->view = view;
	view_update(img);
	return (view);
}

void	view_update(t_image *img)
{
	t_view	*view;
	int		i;

	view = img->view;
	view->to_image = img->pixels_per_line / view->scale;
	view->to_view = view->scale / img->pixels_per_line;
	i = 0;
	while (i < WINDOW_W)
	{
		view->x[i] = (i - view->origin.x) * view->to_view;
		i++;
	}
	i = 0;
	while (i < WINDOW_H)
	{
		view->y[i] = -(i - view->origin.y) * view->to_view;
		i++;
	}
	view->top = view->to_view * view->origin.y;
	view->left = view->to_view * -view->origin.x;
	view->right = view->to_view * (WINDOW_W - view->origin.x - 1);
	view->bottom = view->to_view * -(WINDOW_H - view->origin.y - 1);
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
			z.r = m->img->view->x[v.x];
			z.i = m->img->view->y[v.y];
			color = draw(m, z);
			img_draw_square(m->img, (t_dot){r.x * PREDRAW_RES, r.y * PREDRAW_RES}, (t_dot){PREDRAW_RES, PREDRAW_RES}, color);
			r.y++;
		}
		r.x++;
	}
}

void	view_draw(t_m *m, int (*draw)(t_m*, t_complex))
{
	int	x;
	int	y;
	int	color;
	t_view *view;

	view = m->img->view;
	if (m->is_predraw)
		return (view_predraw(m, draw));
	x = 0;
	while (x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			color = draw(m, (t_complex){view->x[x], view->y[y]});
			img_put_pixel(m->img, x, y, color);
			y++;
		}
		x++;
	}
}
