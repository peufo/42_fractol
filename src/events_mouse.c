/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 12:19:48 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_mouse_move(int x, int y, t_m *m)
{
	if (m->is_mouse_grab)
	{
		m->view.origin.x = (x - m->grab.x);
		m->view.origin.y = (y - m->grab.y);
		view_update(m);
	}
	if (m->is_key.ctrl)
	{
		m->c.r = 0.5 * (x - (WINDOW_W / 2)) * m->view.pixel_to_view;
		m->c.i = 0.5 * -(y - (WINDOW_H / 2)) * m->view.pixel_to_view;
		request_render(m);
	}
	return (0);
}

static int	handle_mousdown(int button, int x, int y, t_m *m)
{
	if (button == BUTTON_LEFT)
	{
		m->is_mouse_grab = 1;
		m->grab.x = x - m->view.origin.x;
		m->grab.y = y - m->view.origin.y;
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
		m->is_mouse_grab = 0;
	return (0);
}

void	events_mouse_init(t_m *m)
{
	m->is_mouse_grab = 0;
	mlx_hook(m->win, ButtonPress, ButtonPressMask, handle_mousdown, m);
	mlx_hook(m->win, ButtonRelease, ButtonReleaseMask, handle_mouseup, m);
	mlx_hook(m->win, MotionNotify, PointerMotionMask, handle_mouse_move, m);
}
