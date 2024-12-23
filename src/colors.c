/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:58:06 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/23 14:51:17 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_colors(t_m *m)
{
	static int	palette_index;

	if (palette_index == 6)
		palette_index = 0;
	m->colors = (t_colors[]){
	{0x19381F, 0xeee82c, 0x91cb3e, 0x53a548, 0x4c934c},
	{0x2c1a1d, 0xdbb3b1, 0xc89fa3, 0xa67f8e, 0x6c534e},
	{0xffbe0b, 0xfb5607, 0xff006e, 0x8338ec, 0x3a86ff},
	{0x565554, 0x2e86ab, 0xf6f5ae, 0xf5f749, 0xf24236},
	{0x1f271b, 0xdcc7be, 0xcbb9a8, 0x145c9e, 0x0b4f6c},
	{0xf17300, 0xdbe4ee, 0x81a4cd, 0x3e7cb1, 0x054a91}
	}[palette_index++];
}

static int	gradient(int a, int b, float ratio)
{
	a = a % 256;
	b = b % 256;
	if (a < b)
		return (a + ratio * (b - a));
	return (a - ratio * (a - b));
}

static int	compute_gradient(int color_a, int color_b, float ratio)
{
	int	color;

	color = 0;
	color += gradient(color_a >> 16, color_b >> 16, ratio) << 16;
	color += gradient(color_a >> 8, color_b >> 8, ratio) << 8;
	color += gradient(color_a, color_b, ratio);
	return (color);
}

int	get_gradient(t_m *m, t_bound b)
{
	double	magni;
	float	i;

	magni = b.magnitude;
	i = (float)b.i;
	if (magni < 4)
		return (m->colors.a);
	if (m->is_color_i)
	{
		if (i <= 10)
			return (compute_gradient(m->colors.e, m->colors.d, i / 10));
		if (i <= 30)
			return (compute_gradient(m->colors.d, m->colors.c, (i - 10) / 20));
		if (i <= 50)
			return (compute_gradient(m->colors.c, m->colors.b, (i - 30) / 20));
		return (m->colors.b);
	}
	if (magni < 8)
		return (compute_gradient(m->colors.b, m->colors.c, (magni - 4) / 4));
	if (magni < 12)
		return (compute_gradient(m->colors.c, m->colors.d, (magni - 8) / 4));
	if (magni < 16)
		return (compute_gradient(m->colors.d, m->colors.e, (magni - 12) / 4));
	return (m->colors.e);
}
