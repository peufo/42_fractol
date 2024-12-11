/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 19:58:52 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_image	*img_get(t_image *img)
{
	static t_image	*_img;

	if (img)
		_img = img;
	return (_img);
}

#include <stdio.h>
void	img_init(void *mlx_ptr, t_image *img, int width, int height)
{
	img->data = mlx_new_image(mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(
			img->data,
			&img->bits_per_pixel,
			&img->bytes_per_line,
			&img->endian);
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	img->pixels_per_line = img->bytes_per_line / img->bytes_per_pixel;
	view_init(img);
	img_get(img);
}

void	img_put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;
	long	offset;

	offset = (y * img->bytes_per_line + x * img->bytes_per_pixel);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	img_draw_square(t_image *img, t_dot position, t_dot size, int color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	end_x = limit(position.x + size.x, WINDOW_W);
	end_y = limit(position.y + size.y, WINDOW_H);
	x = position.x;
	while (x < end_x)
	{
		y = position.y;
		while (y < end_y)
			img_put_pixel(img, x, y++, color);
		x++;
	}
}
