/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:12:05 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 23:51:36 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "ft_printf.h"
# define WINDOW_W 800
# define WINDOW_H 600
# define SCALE 4.0
# define ZOOM_SPEED 0.2
# define MAX_ITERATION 256
# define PREDRAW_RES 5

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
typedef struct s_dot_long
{
	long	x;
	long	y;
}	t_dot_long;
typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;
typedef struct s_bound
{
	t_complex	z;
	int			i;
	double		magnitude;
}	t_bound;
typedef struct s_view
{
	t_dot_long	origin;
	double		x[WINDOW_W];
	double		y[WINDOW_H];
	double		scale;
	double		to_image;
	double		to_view;
	double		top;
	double		left;
	double		right;
	double		bottom;
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
typedef struct s_colors
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
}	t_colors;
typedef struct s_m
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_dot_long	grab;
	t_colors	colors;
	short		is_grab;
	short		is_predraw;
}	t_m;

void		terminate(char *error);
void		events_init(t_m *m);
void		render(t_m *m);
void		zoom(t_m *m, int x, int y, double z);
void		move(t_m *m, int x, int y);

t_image		*img_create(void *mlx_ptr, int width, int height);
void		img_destroy(t_image *img);
void		img_put_pixel(t_image *img, int x, int y, int color);
void		img_draw_square(t_image *img,
				t_dot position,
				t_dot size,
				int color);

t_view		*view_create(t_image *img);
void		view_update(t_image *img);
void		view_draw(t_m *m, int (*draw)(t_m*, t_complex));

t_complex	complex_add(t_complex a, t_complex b);
t_complex	complex_multiply(t_complex a, t_complex b);
double		complex_magnitude(t_complex z);
t_bound		complex_bounded(t_m *m, t_complex z, t_complex c);

int			limit_sup(int v, int limit);
int			limit_inf(int v, int limit);
double		double_limit(double v, double limit);
int			ternaire(int expr, int if_true, int if_false);
void		set_colors(t_m *m);
int			get_gradient(t_m *m, double magnitude);

#endif