/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:12:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/12 22:52:47 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "ft_printf.h"
# define WINDOW_W 800
# define WINDOW_H 600
# define SCALE 4.0
# define ZOOM_SPEED 0.02

enum
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 2,
	BUTTON_MIDDLE = 3,
	BUTTON_SCROLL_UP = 4,
	BUTTON_SCROLL_DOWN = 5
};
enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_dot
{
	int	x;
	int	y;
}	t_dot;
typedef struct s_view
{
	t_dot	origin;
	double	scale;
	double	to_image;
	double	to_view;
	double	top;
	double	left;
	double	right;
	double	bottom;
}	t_view;
typedef struct s_image
{
	void	*data;
	char	*addr;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		bytes_per_line;
	int		bytes;
	int		pixels_per_line;
	int		endian;
	t_view	*view;
}	t_image;
typedef struct s_m
{
	void	*mlx;
	void	*win;
	t_image	*img;
	short	is_grab;
	t_dot	grab;
}	t_m;

void	terminate(char *error);
void	events_init(t_m *m);
void	render(t_m *m);

t_image	*img_create(void *mlx_ptr, int width, int height);
void	img_destroy(t_image *img);
void	img_put_pixel(t_image *img, int x, int y, int color);
void	img_draw_square(t_image *img, t_dot position, t_dot size, int color);

t_view	*view_create(t_image *img);
void	view_update(t_image *img);
void	view_put_pixel(t_image *img, double x, double y, int color);
void	view_draw_line_v(t_image *img, double x, int color);
void	view_draw_line_h(t_image *img, double y, int color);

int		min(int a, int b);
int		max(int a, int b);
int		limit(int v, int limit);

#endif