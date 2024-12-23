/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:50:22 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/23 14:27:56 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(t_m *m, t_complex *z)
{
	t_bound	bound;

	complex_bounded(&bound, m, z);
	return (get_gradient(m, bound));
}

void	render(t_m *m)
{
	clock_t	start = clock();
	unsigned long	time;

	img_draw_square(
		m,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);
	view_draw(m, get_color);
	time = ((clock() - start) * 1000) / CLOCKS_PER_SEC;
	printf("render in %ldms\n", time);
	mlx_put_image_to_window(m->mlx, m->win, m->img.data, 0, 0);
}
