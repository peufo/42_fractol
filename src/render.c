/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 13:45:47 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define COLOR_A 0xD4781A
#define COLOR_B 0xAA3678

static int	get_color(t_complex z)
{
	double	magnitude;

	z = complex_divergence(z);
	magnitude = complex_magnitude(z);
	if (magnitude < 4)
		return (COLOR_A);
	return (COLOR_B);
}

void	render(t_m *m)
{
	img_draw_square(
		m->img,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);
	view_draw(m->img, get_color);
	mlx_put_image_to_window(m->mlx, m->win, m->img->data, 0, 0);
}
