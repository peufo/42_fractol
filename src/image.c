/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 13:35:59 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_destroy(t_image *img)
{
	if (!img)
		return ;
	if (img->view)
		free(img->view);
	free(img);
}

t_image	*img_create(void *mlx_ptr, int width, int height)
{
	t_image	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (terminate("Malloc failed"), NULL);
	img->data = mlx_new_image(mlx_ptr, width, height);
	if (!img->data)
		return (terminate("Image creation failed"), NULL);
	img->addr = mlx_get_data_addr(
			img->data,
			&img->bits_per_pixel,
			&img->bytes_per_line,
			&img->endian);
	if (!img->addr)
		return (terminate("Image creation failed"), NULL);
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	img->pixels_per_line = img->bytes_per_line / img->bytes_per_pixel;
	img->bytes = img->bytes_per_line * height;
	view_create(img);
	return (img);
}

void	img_put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;
	long	offset;

	offset = (y * img->bytes_per_line + x * img->bytes_per_pixel);
	if (offset > img->bytes)
	{
		printf("bytes: %d offset: %ld x: %d, y:%d", img->bytes, offset, x, y);
		return (terminate("Try to draw pixel outside memory"));
	}
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	img_draw_square(t_image *img, t_dot position, t_dot size, int color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	end_x = limit_sup(position.x + size.x, WINDOW_W);
	end_y = limit_sup(position.y + size.y, WINDOW_H);
	x = position.x;
	while (x < end_x)
	{
		y = position.y;
		while (y < end_y)
			img_put_pixel(img, x, y++, color);
		x++;
	}
}
