/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 13:28:33 by jvoisard         ###   ########.fr       */
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
	int	i;

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

void	view_put_pixel(t_image *img, double x, double y, int color)
{
	int		img_x;
	int		img_y;

	img_x = img->view->origin.x + (x * img->view->to_image);
	img_y = img->view->origin.y - (y * img->view->to_image);
	img_put_pixel(img, img_x, img_y, color);
}

void	view_draw_line_v(t_image *img, double x, int color)
{
	double	y;

	if (!(img->view->left <= x && x <= img->view->right))
		return ;
	y = img->view->bottom;
	while (y < img->view->top)
	{
		view_put_pixel(img, x, y, color);
		y += img->view->to_view;
	}
}

void	view_draw_line_h(t_image *img, double y, int color)
{
	double	x;

	if (!(img->view->bottom <= y && y <= img->view->top))
		return ;
	x = img->view->left;
	while (x < img->view->right)
	{
		view_put_pixel(img, x, y, color);
		x += img->view->to_view;
	}
}

static void	view_predraw(
	t_m *m,
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
			color = draw((t_complex){
				.r = m->img->view->x[view_x],
				.i = m->img->view->y[view_y],
			});
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

void	view_draw(t_m *m, int (*draw)(t_complex))
{
	int	x;
	int	y;
	int	color;
	int	predraw[WINDOW_W / PREDRAW_RES][WINDOW_H / PREDRAW_RES];

	view_predraw(m, predraw, draw);
	x = 0;
	while (x < WINDOW_W)
	{
		y = 0;
		while (y < WINDOW_H)
		{
			if (is_interesting(predraw, x, y))
				color = draw((t_complex){
					.r = m->img->view->x[x],
					.i = m->img->view->y[y]
				});
			else
				color = predraw[(int)(x / PREDRAW_RES)][(int)(y / PREDRAW_RES)];
			img_put_pixel(m->img, x, y, color);
			y++;
		}
		x++;
	}
}
