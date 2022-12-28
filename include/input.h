/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:09:30 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/12/27 01:08:09 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
/**
 * All sorts of keyboard keycodes.
 *
 * KP = Keypad.
 */
typedef enum keys
{
	KEY_LEFT_SHIFT		= 257,
	KEY_RIGHT_SHIFT		= 258,
	KEY_SPACE			= 32,
	KEY_Q				= 118,
	KEY_W				= 119,
	KEY_E				= 14,
	KEY_R				= 15,
	KEY_T				= 17,
	KEY_Y				= 16,
	KEY_U				= 32,
	KEY_I				= 34,
	KEY_O				= 31,
	KEY_P				= 35,
	KEY_A				= 97,
	KEY_S				= 115,
	KEY_D				= 100,
	KEY_F				= 3,
	KEY_G				= 5,
	KEY_H				= 4,
	KEY_J				= 38,
	KEY_K				= 40,
	KEY_L				= 37,
	KEY_Z				= 6,
	KEY_X				= 7,
	KEY_C				= 8,
	KEY_V				= 9,
	KEY_B				= 11,
	KEY_N				= 45,
	KEY_M				= 46,
	KEY_ENTER			= 65293,
	KEY_TAB				= 48,
	KEY_RIGHT			= 65363,
	KEY_LEFT			= 65361,
	KEY_DOWN			= 65364,
	KEY_UP				= 65362,
	KEY_LEFT_BRACKET	= 91,
	KEY_BACKSLASH		= 92,
	KEY_RIGHT_BRACKET	= 93,
	KEY_GRAVE_ACCENT	= 96,
	KEY_ESCAPE			= 65307,
	KEY_PLUS			= 69,
	KEY_MINUS			= 78,
}	t_keys;

#endif