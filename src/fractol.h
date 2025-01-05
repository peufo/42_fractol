/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:12:05 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 16:48:57 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <unistd.h>
# include <X11/X.h>
# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"
# include "keys.h"
# define WINDOW_W 1200
# define WINDOW_H 800
# define ZOOM_SPEED 0.2
# define MAX_ITERATION 256
# define LOW_RES 4

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
	double		pixel_to_view;
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
}	t_image;
typedef struct s_colors
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;
}	t_colors;
typedef struct s_keys
{
	short	ctrl;
	short	left;
	short	right;
	short	up;
	short	down;
}	t_keys;
typedef struct s_m	t_m;
typedef struct s_fractal
{
	double		scale;
	t_dot_long	origin;
	void		(*iteration)(t_m *m, t_complex *z, t_complex *c);
}	t_fractal;
struct s_m
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_view		view;
	t_dot_long	grab;
	t_colors	colors;
	t_fractal	fractal;
	t_keys		is_key;
	t_complex	c;
	short		rendering_requested;
	short		is_mouse_grab;
	short		is_low_res;
	short		is_color_i;
};

void	terminate(t_m *m, char *error);
void	events_mouse_init(t_m *m);
void	events_key_init(t_m *m);
int		render(t_m *m);
int		request_render(t_m *m);
void	zoom(t_m *m, int x, int y, double z);
void	move(t_m *m, int x, int y);
void	fractal_set(t_m *m, int fractal_num);

void	img_init(t_m *m);
void	img_put_pixel(t_m *m, int x, int y, int color);
void	img_draw_square(t_m *m, t_dot position, t_dot size, int color);

void	view_init(t_m *m);
void	view_update(t_m *m);
void	view_draw(t_m *m, int (*draw)(t_m*, t_complex*));

float	ft_atof(char *s);
void	set_colors(t_m *m);
int		get_gradient(t_m *m, t_bound bound);

#endif