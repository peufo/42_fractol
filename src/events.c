/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:21:31 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 21:19:58 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static int	handle_mouse_move(int x, int y, void *param)
{
	(void)param;
	printf("x: %d\ny: %d\n", x, y);
	return (0);
}

static int	handle_destroy(void *param)
{
	(void)param;
	terminate(NULL);
	return (0);
}

static int	handle_keydown(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
		return (handle_destroy(NULL));
	return (0);
}

void	events_init(void *mlx_win)
{
	mlx_hook(mlx_win, ON_MOUSEMOVE, 0, handle_mouse_move, NULL);
	mlx_hook(mlx_win, ON_KEYDOWN, 0, handle_keydown, NULL);
	mlx_hook(mlx_win, ON_DESTROY, 0, handle_destroy, NULL);
}
