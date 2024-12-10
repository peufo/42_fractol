/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:11:07 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/10 15:57:07 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void	init_image(void *mlx_ptr, t_image *img, int width, int height)
{
	img->img = mlx_new_image(mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(
		img->img,
		&img->bits_per_pixel,
		&img->line_length, 
		&img->endian);
	img->bytes_per_pixel = img->bits_per_pixel / 8;
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;
	long	offset;

	offset = (y * img->line_length + x * img->bytes_per_pixel);
	dst = img->addr + offset;
	*(unsigned int*)dst = color;
}