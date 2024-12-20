/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:48:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 11:23:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_m *m, int x, int y, double z)
{
	m->img->view->scale *= z;
	m->img->view->origin.x -= (x - m->img->view->origin.x) * ((1 / z) - 1);
	m->img->view->origin.y -= (y - m->img->view->origin.y) * ((1 / z) - 1);
	view_update(m);
	render(m);
}

void	move(t_m *m, int x, int y)
{
	m->img->view->origin.x -= x;
	m->img->view->origin.y += y;
	view_update(m);
	render(m);
}
