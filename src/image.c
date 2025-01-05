/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 16:47:25 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_init(t_m *m)
{
	m->img.data = mlx_new_image(m->mlx, WINDOW_W, WINDOW_H);
	if (!m->img.data)
		return (terminate(m, "MLX new image failed"));
	m->img.addr = mlx_get_data_addr(
			m->img.data,
			&m->img.bits_per_pixel,
			&m->img.bytes_per_line,
			&m->img.endian);
	if (!m->img.addr)
		return (terminate(m, "MLX image get adress failed"));
	m->img.bytes_per_pixel = m->img.bits_per_pixel / 8;
	m->img.pixels_per_line = m->img.bytes_per_line / m->img.bytes_per_pixel;
	m->img.bytes = m->img.bytes_per_line * WINDOW_H;
}

void	img_put_pixel(t_m *m, int x, int y, int color)
{
	char	*dst;
	long	offset;
	t_image	*img;

	img = &m->img;
	offset = (y * img->bytes_per_line + x * img->bytes_per_pixel);
	if (offset > img->bytes)
	{
		ft_printf("bytes: %d offset: %d x: %d, y:%d", img->bytes, offset, x, y);
		return (terminate(m, "Try to draw pixel outside memory"));
	}
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

static int	limit_sup(int v, int limit)
{
	if (v > limit)
		return (limit);
	return (v);
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
