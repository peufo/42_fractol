/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:41:32 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/17 13:52:17 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	limit(int v, int limit)
{
	if (v > limit)
		return (limit);
	return (v);
}

double	double_limit(double v, double limit)
{
	if (v > limit)
		return (limit);
	return (v);
}
