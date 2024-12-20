/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:55:18 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	terminate(t_m *m, char *error)
{
	if (m)
	{
		if (m->img.data)
			mlx_destroy_image(m->mlx, m->img.data);
		mlx_destroy_window(m->mlx, m->win);
	}
	if (error)
	{
		ft_printf("Error: %s\n", error);
		exit(1);
	}
	exit(0);
}

static int	handle_destroy(t_m *m)
{
	terminate(m, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_m	m;

	(void)ac;
	(void)av;
	m.mlx = mlx_init();
	if (!m.mlx)
		return (terminate(&m, "MLX init failed"), 1);
	m.win = mlx_new_window(m.mlx, WINDOW_W, WINDOW_H, "FRAAAAACTOL");
	if (!m.win)
		return (terminate(&m, "MLX new window failed"), 1);
	img_init(&m);
	view_init(&m);
	set_colors(&m);
	events_mouse_init(&m);
	events_key_init(&m);
	render(&m);
	mlx_hook(m.win, ON_DESTROY, 0, handle_destroy, &m);
	mlx_loop(m.mlx);
	return (0);
}
