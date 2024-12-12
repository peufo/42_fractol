/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/12 02:02:31 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

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

	view = img->view;
	view->to_image = img->pixels_per_line / view->scale;
	view->to_view = view->scale / img->pixels_per_line;
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
