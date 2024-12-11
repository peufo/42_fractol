/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:01 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 20:13:00 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	view_init(t_image *img)
{
	img->view = malloc(sizeof(*img->view));
	if (!img->view)
		return (terminate("Malloc failed"));
	img->view->scale = SCALE;
	img->view->origin.x = WINDOW_W / 2;
	img->view->origin.y = WINDOW_H / 2;
	img->view->to_image = img->pixels_per_line / img->view->scale;
	img->view->to_view = img->view->scale / img->pixels_per_line;
	img->view->top = img->view->to_view * img->view->origin.y;
	img->view->left = img->view->to_view * -img->view->origin.x;
	img->view->right = img->view->to_view * (WINDOW_W - img->view->origin.x);
	img->view->bottom = img->view->to_view * -(WINDOW_H - img->view->origin.y);
	printf("to_view %f\n", img->view->to_view);
	printf("to_image %f\n", img->view->to_image);
	printf("top %f\n", img->view->top);
	printf("left %f\n", img->view->left);
	printf("right %f\n", img->view->right);
	printf("bottom %f\n", img->view->bottom);
}

void	view_put_pixel(t_image *img, float x, float y, int color)
{
	int		img_x;
	int		img_y;

	img_x = img->view->origin.x + (x * img->view->to_image);
	img_y = img->view->origin.y - (y * img->view->to_image);
	img_put_pixel(img, img_x, img_y, color);
}

void	view_draw_line_v(t_image *img, float x, int color)
{
	float	y;

	y = img->view->bottom;
	printf("y %f\n", y);
	while (y < img->view->top)
	{
		view_put_pixel(img, x, y, color);
		y += img->view->to_view;
	}
}

void	view_draw_line_h(t_image *img, float y, int color)
{
	float	x;
 
	x = img->view->left;
	while (x < img->view->right)
	{
		view_put_pixel(img, x, y, color);
		x += img->view->to_view;
	}
	
}
