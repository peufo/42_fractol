/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:24:59 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/21 01:40:33 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	ft_atof(char *s)
{
	int	before;
	int	after;
	int	len_after;
	int	sign;

	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		sign -= (*(s++) == '-') * 2;
	before = ft_atoi(s);
	after = 0;
	while (*s && *s != '.')
		s++;
	if (*s == '.')
	{
		after = ft_atoi(s + 1);
		len_after = ft_strlen(s + 1);
		return (sign * (before + ((float)after * pow(10, -len_after))));
	}
	return (sign * (float)before);
}
