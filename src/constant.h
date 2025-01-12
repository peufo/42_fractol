/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:26:37 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/12 18:22:44 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_H
# define CONSTANT_H
# ifdef __linux__
#  include <X11/X.h>
# endif

enum
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 2,
	BUTTON_MIDDLE = 3,
	BUTTON_SCROLL_UP = 4,
	BUTTON_SCROLL_DOWN = 5
};

# ifdef __APPLE__

#  define ON_KEY_DOWN 2
#  define ON_KEY_UP 3
#  define ON_MOUSEDOWN 4
#  define ON_MOUSEUP 5
#  define ON_MOUSEMOVE 6
#  define ON_EXPOSE 12
#  define ON_DESTROY 17
#  define ON_KEY_DOWN_MASK 0
#  define ON_KEY_UP_MASK 0
#  define ON_MOUSEDOWN_MASK 0
#  define ON_MOUSEUP_MASK 0
#  define ON_MOUSEMOVE_MASK 0
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

#  define ON_KEY_DOWN KeyPress
#  define ON_KEY_UP KeyRelease
#  define ON_MOUSEDOWN ButtonPress
#  define ON_MOUSEUP ButtonRelease
#  define ON_MOUSEMOVE MotionNotify
#  define ON_EXPOSE 12
#  define ON_DESTROY DestroyNotify
#  define ON_KEY_DOWN_MASK KeyPressMask
#  define ON_KEY_UP_MASK KeyReleaseMask
#  define ON_MOUSEDOWN_MASK ButtonPressMask
#  define ON_MOUSEUP_MASK ButtonReleaseMask
#  define ON_MOUSEMOVE_MASK PointerMotionMask
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