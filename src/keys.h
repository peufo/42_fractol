/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:26:37 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 14:27:47 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__

#  define KEY_ESCAPE 53
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_C 8
#  define KEY_SPACE 49
#  define KEY_M 46
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_R 15
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_CTRL 260
#  define KEY_CMD 256

# elif __linux__

#  define KEY_ESCAPE 65307
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_C 99
#  define KEY_SPACE 32
#  define KEY_M 109
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_R 114
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_UP 65362
#  define KEY_CTRL 65507
#  define KEY_CMD 65507

# endif

#endif