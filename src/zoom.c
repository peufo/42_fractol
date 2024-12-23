/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:48:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/23 14:47:37 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_m *m, int x, int y, double z)
{
	m->view.scale *= z;
	m->view.origin.x -= (x - m->view.origin.x) * ((1 / z) - 1);
	m->view.origin.y -= (y - m->view.origin.y) * ((1 / z) - 1);
	view_update(m);
}

void	move(t_m *m, int x, int y)
{
	m->view.origin.x -= x;
	m->view.origin.y += y;
	view_update(m);
}
