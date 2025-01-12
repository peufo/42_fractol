/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:24:31 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/12 18:28:41 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef __linux__
# define DESTROY_DISPLAY mlx_destroy_display
#else
# define DESTROY_DISPLAY do_noting
#endif

static int	do_noting(void *mlx)
{
	(void)mlx;
	return (1);
}

void	destroy_display(t_m *m)
{
	DESTROY_DISPLAY(m->mlx);
}
