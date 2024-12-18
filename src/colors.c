/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:58:06 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/19 00:02:56 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_colors(t_m *m)
{
	static int	palette_index;
	if (palette_index == 4)
		palette_index = 0;
	m->colors = (t_colors[]){
	{0x19381F, 0xeee82c, 0x91cb3e, 0x53a548, 0x4c934c},
	{0x2c1a1d, 0xdbb3b1, 0xc89fa3, 0xa67f8e, 0x6c534e},
	{0xffbe0b, 0xfb5607, 0xff006e, 0x8338ec, 0x3a86ff},
	{0x565554, 0x2e86ab, 0xf6f5ae, 0xf5f749, 0xf24236}
	}[palette_index++];
}

static int gradient(int a, int b, float ratio)
{
	a = a % 256;
	b = b % 256;
	if (a < b)
		return (a + ratio * (b - a));
	return (a - ratio * (a - b));
}

static int	compute_gradient(int color_a, int color_b, float ratio)
{
	int color;

	color = 0;
	color += gradient(color_a >> 16, color_b >> 16, ratio) << 16;
	color += gradient(color_a >> 8, color_b >> 8, ratio) << 8;
	color += gradient(color_a, color_b, ratio);
	return (color);
}

int	get_gradient(t_m *m, double magnitude)
{
	if (magnitude < 4)
		return (m->colors.a);
	if (magnitude < 8)
		return (compute_gradient(m->colors.b, m->colors.c, (magnitude - 4) / 4));
	if (magnitude < 12)
		return (compute_gradient(m->colors.c, m->colors.d, (magnitude - 8) / 4));
	if (magnitude < 16)
		return (compute_gradient(m->colors.d, m->colors.e, (magnitude - 12) / 4));
	return (m->colors.e);
}
