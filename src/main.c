/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 21:18:17 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_m *save(t_m *m)
{
	static t_m *_m;

	if (m)
		_m = m;
	return (_m);
}

void	terminate(char *error)
{
	t_m	*m;

	m = save(NULL);
	if (m && m->img && m->img->view)
	{
		free(m->img->view);
		m->img->view = NULL;
	}
	if (m && m->img)
	{
		free(m->img);
		m->img = NULL;
	}
	if (m)
		mlx_destroy_window(m->mlx, m->win);
	if (error)
	{
		ft_printf("Error: %s\n", error);
		exit(1);
	}
	exit(0);
}

int	main(int ac, char **av)
{
	t_m	m;

	(void)ac;
	(void)av;
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINDOW_W, WINDOW_H, "FRAAAAACTOL");
	m.img = img_create(m.mlx, WINDOW_W, WINDOW_H);
	save(&m);

	img_draw_square(
		m.img,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);
	view_draw_line_v(m.img, -1, 0x000000);
	view_draw_line_v(m.img, 0, 0x000000);
	view_draw_line_v(m.img, 1, 0x000000);
	view_draw_line_h(m.img, -1, 0x000000);
	view_draw_line_h(m.img, 0, 0x000000);
	view_draw_line_h(m.img, 1, 0x000000);
	mlx_put_image_to_window(m.mlx, m.win, m.img->data, 0, 0);
	events_init(m.win);
	mlx_loop(m.mlx);
	return (0);
}
