/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/10 16:57:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_image	img;

	(void)ac;
	(void)av;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 700, "YOOOO");
	
	init_image(mlx, &img, 1000, 700);

	draw_square(&img, (t_dot){ .x = 50, .y = 50}, (t_dot){400, 400}, 0xff0000);
	draw_square(&img, (t_dot){ .x = 100, .y = 100}, (t_dot){400, 400}, 0xffff00);
	draw_square(&img, (t_dot){ .x = 150, .y = 150}, (t_dot){400, 400}, 0x00ff00);
	draw_square(&img, (t_dot){ .x = 200, .y = 200}, (t_dot){400, 400}, 0x00ffff);
	draw_square(&img, (t_dot){ .x = 250, .y = 250}, (t_dot){400, 400}, 0x0000ff);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}
