/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 23:02:15 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

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

static int	handle_scroll(int button, int x, int y, t_m *m)
{
	(void)x;
	(void)y;
	if (button == BUTTON_SCROLL_UP)
	{
		if (m->img->view->scale < 0.8)
			return (0);
		m->img->view->scale *= 0.98;
		view_update(m->img);
		render(m);
	}
	if (button == BUTTON_SCROLL_DOWN)
	{
		m->img->view->scale *= 1.02;
		view_update(m->img);
		render(m);
	}
	return (0);
}

void	events_init(t_m *m)
{
	mlx_hook(m->win, ON_MOUSEDOWN, 0, handle_scroll, m);
	mlx_hook(m->win, ON_KEYDOWN, 0, handle_keydown, m);
	mlx_hook(m->win, ON_DESTROY, 0, handle_destroy, m);
}
