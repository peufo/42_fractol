/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/12 23:00:43 by jvoisard         ###   ########.fr       */
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

static int handle_mouse_move(int x, int y, t_m *m)
{

	if (!m->is_grab)
		return (0);
	m->img->view->origin.x = (x - m->grab.x);
	m->img->view->origin.y = (y - m->grab.y);
	view_update(m->img);
	render(m);
	return (0);
}

static int	handle_keydown(int keycode, t_m *m)
{
	(void)m;
	if (keycode == 53)
		return (handle_destroy(NULL));
	if (keycode == 15)
	{
		m->img->view->scale = SCALE;
		m->img->view->origin.x = WINDOW_W / 2;
		m->img->view->origin.y = WINDOW_H / 2;
		view_update(m->img);
		render(m);
	}
	return (0);
}

static int	handle_mousdown(int button, int x, int y, t_m *m)
{
	if (button == BUTTON_LEFT)
	{
		m->is_grab = 1;
		m->grab.x = x - m->img->view->origin.x;
		m->grab.y = y - m->img->view->origin.y;
		return (0);
	}
	if (button == BUTTON_SCROLL_UP)
	{
		m->img->view->scale *= 1 - ZOOM_SPEED;
		m->img->view->origin.x -= (x - m->img->view->origin.x) * ZOOM_SPEED;
		m->img->view->origin.y -= (y - m->img->view->origin.y) * ZOOM_SPEED;
		view_update(m->img);
		render(m);
	}
	if (button == BUTTON_SCROLL_DOWN)
	{
		m->img->view->scale *= 1 + ZOOM_SPEED;
		m->img->view->origin.x += (x - m->img->view->origin.x) * ZOOM_SPEED;
		m->img->view->origin.y += (y - m->img->view->origin.y) * ZOOM_SPEED;
		view_update(m->img);
		render(m);
	}
	return (0);
}

static int handle_mouseup(int button, int x, int y, t_m *m)
{
	(void)x;
	(void)y;
	if (button == BUTTON_LEFT)
		m->is_grab = 0;
	return (0);
}

void	events_init(t_m *m)
{
	mlx_hook(m->win, ON_MOUSEDOWN, 0, handle_mousdown, m);
	mlx_hook(m->win, ON_MOUSEUP, 0, handle_mouseup, m);
	mlx_hook(m->win, ON_MOUSEMOVE, 0, handle_mouse_move, m);
	mlx_hook(m->win, ON_KEYDOWN, 0, handle_keydown, m);
	mlx_hook(m->win, ON_DESTROY, 0, handle_destroy, m);
}
