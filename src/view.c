/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 13:45:14 by jvoisard         ###   ########.fr       */
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

static void	view_predraw(
	t_view *view,
	int predraw[WINDOW_W / PREDRAW_RES][WINDOW_H / PREDRAW_RES],
	int (*draw)(t_complex))
{
	int	x;
	int	y;
	int	view_x;
	int	view_y;
	int	color;

	x = 0;
	while (x < WINDOW_W / PREDRAW_RES)
	{
		y = 0;
		while (y < WINDOW_H / PREDRAW_RES)
		{
			view_x = x * PREDRAW_RES + PREDRAW_RES / 2;
			view_y = y * PREDRAW_RES + PREDRAW_RES / 2;
			color = draw((t_complex){view->x[view_x], view->y[view_y]});
			predraw[x][y] = color;
			y++;
		}
		x++;
	}
}

static short	is_interesting(
	int predraw[WINDOW_W / PREDRAW_RES][WINDOW_H / PREDRAW_RES],
	int view_x,
	int view_y)
{
	int	x;
	int	y;
	int	_x;
	int	_y;

	x = (int)(view_x / PREDRAW_RES);
	y = (int)(view_y / PREDRAW_RES);
	_x = limit_inf(x - 1, 0);
	while (_x <= limit_sup(x + 1, WINDOW_W / PREDRAW_RES))
	{
		_y = limit_inf(y - 1, 0);
		while (_y <= limit_sup(y + 1, WINDOW_W / PREDRAW_RES))
		{
			if (predraw[x][y] != predraw[_x][_y])
				return (1);
			_y++;
		}
		_x++;
	}
	return (0);
}

void	view_draw(t_image *img, int (*draw)(t_complex))
{
	int	x;
	int	y;
	int	color;
	int	predraw[WINDOW_W / PREDRAW_RES][WINDOW_H / PREDRAW_RES];

	view_predraw(img->view, predraw, draw);
	x = 0;
	while (x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			if (is_interesting(predraw, x, y))
				color = draw((t_complex){img->view->x[x], img->view->y[y]});
			else
				color = predraw[(int)(x / PREDRAW_RES)][(int)(y / PREDRAW_RES)];
			img_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}
