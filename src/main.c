/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:49:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/21 01:32:20 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	terminate(t_m *m, char *error)
{
	if (m)
	{
		if (m->img.data)
			mlx_destroy_image(m->mlx, m->img.data);
		if (m->mlx && m->win)
			mlx_destroy_window(m->mlx, m->win);
	}
	if (error)
	{
		ft_printf("Error: %s\n", error);
		exit(1);
	}
	exit(0);
}

static int	handle_destroy(t_m *m)
{
	terminate(m, NULL);
	return (0);
}

static int	print_help(void)
{
	ft_printf("\033[1mUsage\033[0m\n");
	ft_printf("./fractol fractal [real] [imaginary]\n");
	ft_printf("\n\033[1mOptions\033[0m\n");
	ft_printf("%-10s = %-7sJulia\t(z -> z^2 + c)\n", "fractal", "1");
	ft_printf("%-10s = %-7sMandelbrot\t(z -> z^2 + z)\n", "fractal", "2");
	ft_printf("%-10s = %-7s(Julia) Set real of c\n", "real", "float");
	ft_printf("%-10s = %-7s(Julia) Set imaginary of c\n", "imaginary", "float");
	ft_printf("\n\033[1mCommandes\033[0m\n");
	ft_printf("%-20sChange color set\n", "[c]");
	ft_printf("%-20sChange color method\n", "[m]");
	ft_printf("%-20sReset view\n", "[r]");
	ft_printf("%-20sZoom in\n", "[w]");
	ft_printf("%-20sZoom out\n", "[s]");
	ft_printf("%-20sToggle low/hight resolution\n", "[ ]");
	ft_printf("%-20s(Julia) Set C with mouse position\n", "[Ctrl]");
	ft_printf("%-20sMove\n", "[direction]");
	ft_printf("%-20sMove\n", "(Mouse left press)");
	ft_printf("%-20sZoom in/out\n", "(Mouse scroll)");
	return (0);
}

static int	parse_args(t_m *m, int ac, char **av)
{
	int	fractal_num;

	if (ac < 2 || 4 < ac)
		return (1);
	fractal_num = ft_atoi(av[1]);
	if (fractal_num < 1 || 2 < fractal_num)
		return (1);
	fractal_set(m, fractal_num);
	if (fractal_num != 1 && ac > 2)
		return (1);
	if (fractal_num != 1)
		return (0);
	if (ac > 2)
		m->c.r = ft_atof(av[2]);
	if (ac > 3)
		m->c.i = ft_atof(av[3]);
	printf("prout %f\n", m->c.r);
	return (0);
}

int	main(int ac, char **av)
{
	t_m	m;

	if (parse_args(&m, ac, av))
		return (print_help());
	m.mlx = mlx_init();
	if (!m.mlx)
		return (terminate(&m, "MLX init failed"), 1);
	m.win = mlx_new_window(m.mlx, WINDOW_W, WINDOW_H, "FRAAAAACTOL");
	if (!m.win)
		return (terminate(&m, "MLX new window failed"), 1);
	img_init(&m);
	events_mouse_init(&m);
	events_key_init(&m);
	set_colors(&m);
	view_init(&m);
	mlx_hook(m.win, ON_DESTROY, 0, handle_destroy, &m);
	mlx_loop(m.mlx);
	return (0);
}
