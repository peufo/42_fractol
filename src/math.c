/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:41:32 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/20 12:42:12 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	limit_sup(int v, int limit)
{
	if (v > limit)
		return (limit);
	return (v);
}

int	limit_inf(int v, int limit)
{
	if (v < limit)
		return (limit);
	return (v);
}

double	double_limit(double v, double limit)
{
	if (v > limit)
		return (limit);
	return (v);
}
