/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:29:42 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 20:39:03 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_window_handler(game);
	if (keycode == K_W)
		game->keys.w = 1;
	if (keycode == K_A)
		game->keys.a = 1;
	if (keycode == K_S)
		game->keys.s = 1;
	if (keycode == K_D)
		game->keys.d = 1;
	if (keycode == K_LEFT)
		game->keys.left = 1;
	if (keycode == K_RIGHT)
		game->keys.right = 1;
	return (SUCCESS);
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == K_W)
		game->keys.w = 0;
	if (keycode == K_A)
		game->keys.a = 0;
	if (keycode == K_S)
		game->keys.s = 0;
	if (keycode == K_D)
		game->keys.d = 0;
	if (keycode == K_LEFT)
		game->keys.left = 0;
	if (keycode == K_RIGHT)
		game->keys.right = 0;
	return (SUCCESS);
}
