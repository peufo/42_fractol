/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:27:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_destroy(t_m *m)
{
	if (!m && !m->img)
		return ;
	if (m->img->view)
		free(m->img->view);
	free(m->img);
}

void	img_init(t_m *m, int width, int height)
{
	t_image	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (terminate(m, "Malloc failed"));
	img->data = mlx_new_image(m->mlx, width, height);
	if (!img->data)
		return (terminate(m, "Image creation failed"));
	img->addr = mlx_get_data_addr(
			img->data,
			&img->bits_per_pixel,
			&img->bytes_per_line,
			&img->endian);
	if (!img->addr)
		return (terminate(m, "Image creation failed"));
	img->bytes_per_pixel = img->bits_per_pixel / 8;
	img->pixels_per_line = img->bytes_per_line / img->bytes_per_pixel;
	img->bytes = img->bytes_per_line * height;
	m->img = img;
	view_init(m);
}

void	img_put_pixel(t_m *m, int x, int y, int color)
{
	char	*dst;
	long	offset;
	t_image	*img;

	img = m->img;
	offset = (y * img->bytes_per_line + x * img->bytes_per_pixel);
	if (offset > img->bytes)
	{
		ft_printf("bytes: %d offset: %d x: %d, y:%d", img->bytes, offset, x, y);
		return (terminate(m, "Try to draw pixel outside memory"));
	}
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	img_draw_square(t_m *m, t_dot position, t_dot size, int color)
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
			img_put_pixel(m, x, y++, color);
		x++;
	}
}
