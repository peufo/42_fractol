/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 22:44:11 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_mouse_move(int x, int y, t_m *m)
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
	if (keycode == 53)
		return (terminate(NULL), 0);
	if (keycode == 8)
		return (set_colors(m), render(m), 0);
	if (keycode == 49)
	{
		m->is_predraw = !m->is_predraw;
		render(m);
	}
	if (keycode == 15)
	{
		m->img->view->scale = SCALE;
		m->img->view->origin.x = WINDOW_W / 2;
		m->img->view->origin.y = WINDOW_H / 2;
		view_update(m->img);
		render(m);
	}
	if (keycode == 123)
		move(m, -(WINDOW_W / 20), 0);
	if (keycode == 124)
		move(m, WINDOW_W / 20, 0);
	if (keycode == 125)
		move(m, 0, -(WINDOW_H / 20));
	if (keycode == 126)
		move(m, 0, WINDOW_H / 20);
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
		zoom(m, x, y, 1 - ZOOM_SPEED);
		return (0);
	}
	if (button == BUTTON_SCROLL_DOWN)
	{
		zoom(m, x, y, 1 + ZOOM_SPEED);
		return (0);
	}
	return (0);
}

static int	handle_mouseup(int button, int x, int y, t_m *m)
{
	(void)x;
	(void)y;
	if (button == BUTTON_LEFT)
		m->is_grab = 0;
	return (0);
}

void	events_init(t_m *m)
{
	m->is_grab = 0;
	mlx_hook(m->win, ON_MOUSEDOWN, 0, handle_mousdown, m);
	mlx_hook(m->win, ON_MOUSEUP, 0, handle_mouseup, m);
	mlx_hook(m->win, ON_MOUSEMOVE, 0, handle_mouse_move, m);
	mlx_hook(m->win, ON_KEYDOWN, 0, handle_keydown, m);
}
