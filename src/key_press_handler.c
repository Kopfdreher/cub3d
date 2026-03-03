/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:29:42 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 16:11:43 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_window_handler(game);
	/*
	 * if (keycode == K_W)
	 * if (keycode == K_A)
	 * if (keycode == K_S)
	 * if (keycode == K_D)
	 * if (keycode == K_LEFT)
	 * if (keycode == K_RIGHT)
		*/
	return (SUCCESS);
}
