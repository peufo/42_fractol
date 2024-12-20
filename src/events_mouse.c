/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:48:32 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_mouse_move(int x, int y, t_m *m)
{
	if (!m->is_mouse_grab)
		return (0);
	m->view.origin.x = (x - m->grab.x);
	m->view.origin.y = (y - m->grab.y);
	view_update(m);
	render(m);
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
	mlx_hook(m->win, ON_MOUSEDOWN, 0, handle_mousdown, m);
	mlx_hook(m->win, ON_MOUSEUP, 0, handle_mouseup, m);
	mlx_hook(m->win, ON_MOUSEMOVE, 0, handle_mouse_move, m);
}
