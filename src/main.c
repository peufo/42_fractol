/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 00:13:45 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_m	*save(t_m *m)
{
	static t_m	*_m;

	if (m)
		_m = m;
	return (_m);
}

void	terminate(char *error)
{
	t_m	*m;

	m = save(NULL);
	if (m && m->img)
		img_destroy(m->img);
	if (m)
		mlx_destroy_window(m->mlx, m->win);
	if (error)
	{
		ft_printf("Error: %s\n", error);
		exit(1);
	}
	exit(0);
}

static int	handle_destroy(t_m *m)
{
	(void)m;
	terminate(NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_m	m;

	(void)ac;
	(void)av;
	save(&m);
	m.mlx = mlx_init();
	if (!m.mlx)
		return (terminate("MLX init failed"), 1);
	m.win = mlx_new_window(m.mlx, WINDOW_W, WINDOW_H, "FRAAAAACTOL");
	if (!m.win)
		return (terminate("MLX new window failed"), 1);
	m.img = img_create(m.mlx, WINDOW_W, WINDOW_H);
	set_colors(&m);
	render(&m);
	events_mouse_init(&m);
	events_key_init(&m);
	mlx_hook(m.win, ON_DESTROY, 0, handle_destroy, &m);
	mlx_loop(m.mlx);
	return (0);
}
