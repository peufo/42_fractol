/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 21:41:49 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static int	handle_mouse_move(int x, int y, t_m *m)
{
	m->mouse.x = x;
	m->mouse.y = y;
	return (0);
}

static int	handle_destroy(t_m *m)
{
	(void)m;
	terminate(NULL);
	return (0);
}

static int	handle_keydown(int keycode, t_m *m)
{
	(void)m;
	if (keycode == 53)
		return (handle_destroy(NULL));
	return (0);
}

void	events_init(t_m *m)
{
	mlx_hook(m->win, ON_MOUSEMOVE, 0, handle_mouse_move, m);
	mlx_hook(m->win, ON_KEYDOWN, 0, handle_keydown, m);
	mlx_hook(m->win, ON_DESTROY, 0, handle_destroy, m);
}
