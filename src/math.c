/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:41:32 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/11 18:10:30 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	limit(int v, int limit)
{
	if (v > limit)
		return (limit);
	return (v);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
