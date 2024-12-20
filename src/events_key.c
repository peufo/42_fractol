/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:31:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	reset_view(t_m *m)
{
	m->view->scale = SCALE;
	m->view->origin.x = WINDOW_W / 2;
	m->view->origin.y = WINDOW_H / 2;
	view_update(m);
	render(m);
}

static void	handle_move(short is_keydown, int keycode, t_m *m)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == 123)
		m->is_key.left = is_keydown;
	if (keycode == 124)
		m->is_key.right = is_keydown;
	if (keycode == 125)
		m->is_key.down = is_keydown;
	if (keycode == 126)
		m->is_key.up = is_keydown;
	if (m->is_key.left ^ m->is_key.right)
		x = (WINDOW_W / 20) * (1 - 2 * m->is_key.left);
	if (m->is_key.up ^ m->is_key.down)
		y = (WINDOW_H / 20) * (1 - 2 * m->is_key.down);
	if (x | y)
		move(m, x, y);
	return ;
}

static int	handle_keydown(int keycode, t_m *m)
{
	if (keycode == 53)
		return (terminate(m, NULL), 0);
	if (keycode == 8)
		return (set_colors(m), render(m), 0);
	if (keycode == 49)
		return (m->is_mode_predraw = !m->is_mode_predraw, render(m), 0);
	if (keycode == 46)
		return (m->is_colored_by_i = !m->is_colored_by_i, render(m), 0);
	if (keycode == 13)
		return (zoom(m, WINDOW_W / 2, WINDOW_H / 2, 1 - ZOOM_SPEED), 0);
	if (keycode == 1)
		return (zoom(m, WINDOW_W / 2, WINDOW_H / 2, 1 + ZOOM_SPEED), 0);
	if (keycode == 15)
		return (reset_view(m), 0);
	if (123 <= keycode && keycode <= 126)
		return (handle_move(1, keycode, m), 0);
	if (keycode == 260 || keycode == 256)
		return (m->is_key.ctrl = 1, 0);
	return (0);
}

static int	handle_keyup(int keycode, t_m *m)
{
	if (123 <= keycode && keycode <= 126)
		handle_move(0, keycode, m);
	if (keycode == 260 || keycode == 256)
		m->is_key.ctrl = 0;
	return (0);
}

void	events_key_init(t_m *m)
{
	m->is_colored_by_i = 1;
	m->is_mode_predraw = 0;
	m->is_key.ctrl = 0;
	m->is_key.down = 0;
	m->is_key.left = 0;
	m->is_key.right = 0;
	m->is_key.up = 0;
	mlx_hook(m->win, ON_KEYDOWN, 0, handle_keydown, m);
	mlx_hook(m->win, ON_KEYUP, 0, handle_keyup, m);
}