/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:09:30 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/24 21:16:59 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

/**
 * A key action such as pressing or releasing a key.
 * 
 * @param RELEASE Execute when the key is being released.
 * @param PRESS Execute when the key is being pressed.
 * @param REPEAT Execute when the key is being held down.
 */
typedef enum action
{
	MLX_RELEASE = 0,
	MLX_PRESS	= 2,
	MLX_REPEAT	= 1,
}	action_t;

/**
 * The mouse button keycodes.
 * @param LEFT The left mouse button.
 * @param RIGHT The right mouse button.
 * @param MIDDLE The middle mouse button, aka the Scrollwheel.
 */
typedef enum mouse_key
{
	MLX_MOUSE_BUTTON_LEFT	= 0,
	MLX_MOUSE_BUTTON_RIGHT	= 1,
	MLX_MOUSE_BUTTON_MIDDLE	= 2,
}	mouse_key_t;

/**
 * Various mouse/cursor states.
 * @param NORMAL Simple visibile default cursor.
 * @param HIDDEN The cursor is not rendered, still functions however.
 * @param DISABLED The cursor is not rendered, nor is it functional.
 */
typedef enum mouse_mode
{
	MLX_MOUSE_NORMAL	= 0x00034001,
	MLX_MOUSE_HIDDEN	= 0x00034002,
	MLX_MOUSE_DISABLED	= 0x00034003,
}	mouse_mode_t;

/**
 * All sorts of keyboard keycodes.
 *
 * KP = Keypad.
 */
typedef enum keys
{
	KEY_LEFT_SHIFT		= 257,
	KEY_RIGHT_SHIFT		= 258,
	KEY_SPACE			= 49,
	KEY_Q				= 12,
	KEY_W				= 13,
	KEY_E				= 14,
	KEY_R				= 15,
	KEY_T				= 17,
	KEY_Y				= 16,
	KEY_U				= 32,
	KEY_I				= 34,
	KEY_O				= 31,
	KEY_P				= 35,
	KEY_A				= 0,
	KEY_S				= 1,
	KEY_D				= 2,
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
	KEY_ENTER			= 36,
	KEY_TAB				= 48,
	KEY_RIGHT			= 124,
	KEY_LEFT			= 123,
	KEY_DOWN			= 125,
	KEY_UP				= 126,
	KEY_LEFT_BRACKET	= 91,
	KEY_BACKSLASH		= 92,
	KEY_RIGHT_BRACKET	= 93,
	KEY_GRAVE_ACCENT	= 96,
	KEY_ESCAPE			= 53,
}	keys_t;

#endif