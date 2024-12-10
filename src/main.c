/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/10 15:58:57 by jvoisard         ###   ########.fr       */
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
	mlx_win = mlx_new_window(mlx, 1000, 700, "WHERE ?");
	
	init_image(mlx, &img, 80, 80);

	put_pixel(&img, 5, 5, 0x0000ff00);
	put_pixel(&img, 7, 5, 0x00ff0000);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}
