/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:48:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 11:49:54 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_camera(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	rot = ROTATE_SPEED;
	if (game->keys.left)
		rot = -ROTATE_SPEED;
	if (game->keys.left || game->keys.right)
	{
		game->player.dir_x = 
			game->player.dir_x * cos(rot) - game->player.dir_y * sin(rot);
		game->player.dir_y = 
			old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
		game->player.plane_x = 
			game->player.plane_x * cos(rot) - game->player.plane_y * sin(rot);
		game->player.plane_y = 
			old_plane_x * sin(rot) + game->player.plane_y * cos(rot);
	}
}

void	move_player(t_game *game)
{
	calc_movement(game);
	rotate_camera(game);
}
