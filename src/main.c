/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 20:13:35 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	terminate(char *error)
{
	t_image	*img;

	img = img_get(NULL);
	if (img && img->view)
	{
		free(img->view);
		img->view = NULL;
	}
	if (error)
	{
		ft_printf("Error: %s\n", error);
		exit(1);
	}
	exit(0);
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_image	img;

	(void)ac;
	(void)av;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_W, WINDOW_H, "FRAAAAACTOL");
	img_init(mlx, &img, WINDOW_W, WINDOW_H);
	img_draw_square(
		&img,
		(t_dot){0, 0},
		(t_dot){WINDOW_W, WINDOW_H},
		0xFFFFFF);

	view_draw_line_v(&img, -1, 0x000000);
	view_draw_line_v(&img, 0, 0x000000);
	view_draw_line_v(&img, 1, 0x000000);

	view_draw_line_h(&img, -1, 0x000000);
	view_draw_line_h(&img, 0, 0x000000);
	view_draw_line_h(&img, 1, 0x000000);
	//img_draw_square(&img, (t_dot){50, 50}, (t_dot){500, 500}, 0xFFF000);
	/*
	view_put_pixel(&img, -1, -1, 0x000000);
	view_put_pixel(&img, 0, -1, 0x000000);
	view_put_pixel(&img, 1, -1, 0x000000);
	view_put_pixel(&img, 1, 1, 0x000000);
	view_put_pixel(&img, 0, 1, 0x000000);
	view_put_pixel(&img, -1, 1, 0x000000);
	view_put_pixel(&img, -1, 0, 0x000000);
	*/
	mlx_put_image_to_window(mlx, mlx_win, img.data, 0, 0);
	mlx_loop(mlx);
	return (0);
}
