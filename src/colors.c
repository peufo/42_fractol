/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:58:06 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/18 21:34:05 by jvoisard         ###   ########.fr       */
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
