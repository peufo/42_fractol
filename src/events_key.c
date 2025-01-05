/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 14:41:56 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_direction_key(int keycode)
{
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		return (1);
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		return (1);
	return (0);
}

static void	handle_move(short is_pressed, int keycode, t_m *m)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == KEY_LEFT)
		m->is_key.left = is_pressed;
	if (keycode == KEY_RIGHT)
		m->is_key.right = is_pressed;
	if (keycode == KEY_DOWN)
		m->is_key.down = is_pressed;
	if (keycode == KEY_UP)
		m->is_key.up = is_pressed;
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
	if (keycode == KEY_ESCAPE)
		return (terminate(m, NULL), 0);
	if (KEY_1 <= keycode && keycode <= KEY_3)
		return (fractal_set(m, keycode - KEY_1 + 1), view_init(m), 0);
	if (keycode == KEY_C)
		return (set_colors(m), request_render(m), 0);
	if (keycode == KEY_SPACE)
		return (m->is_low_res = !m->is_low_res, request_render(m), 0);
	if (keycode == KEY_M)
		return (m->is_color_i = !m->is_color_i, request_render(m), 0);
	if (keycode == KEY_W)
		return (zoom(m, WINDOW_W / 2, WINDOW_H / 2, 1 - ZOOM_SPEED), 0);
	if (keycode == KEY_S)
		return (zoom(m, WINDOW_W / 2, WINDOW_H / 2, 1 + ZOOM_SPEED), 0);
	if (keycode == KEY_R)
		return (view_init(m), 0);
	if (is_direction_key(keycode))
		return (handle_move(1, keycode, m), 0);
	if (keycode == KEY_CTRL || keycode == KEY_CMD)
		return (m->is_key.ctrl = 1, 0);
	return (0);
}

static int	handle_keyup(int keycode, t_m *m)
{
	if (is_direction_key(keycode))
		handle_move(0, keycode, m);
	if (keycode == KEY_CTRL || keycode == KEY_CMD)
		m->is_key.ctrl = 0;
	return (0);
}

void	events_key_init(t_m *m)
{
	m->is_color_i = 1;
	m->is_low_res = 0;
	m->is_key.ctrl = 0;
	m->is_key.down = 0;
	m->is_key.left = 0;
	m->is_key.right = 0;
	m->is_key.up = 0;
	mlx_hook(m->win, KeyPress, KeyPressMask, handle_keydown, m);
	mlx_hook(m->win, KeyRelease, KeyReleaseMask, handle_keyup, m);
}
