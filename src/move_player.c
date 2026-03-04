/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:48:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 20:37:29 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	insert_valid_pos(double new_x, double new_y, t_game *game)
{
	if (game->config.map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->config.map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

static void	move_forward_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = 0.0;
	new_y = 0.0;
	if (game->keys.w && !game->keys.s)
	{
		new_x = game->player.pos_x + game->player.dir_x * MOVEMENT_SPEED;
		new_y = game->player.pos_y + game->player.dir_y * MOVEMENT_SPEED;
	}
	if (game->keys.s && !game->keys.w)
	{
		new_x = game->player.pos_x - game->player.dir_x * MOVEMENT_SPEED;
		new_y = game->player.pos_y - game->player.dir_y * MOVEMENT_SPEED;
	}
	if (game->keys.w || game->keys.s)
		insert_valid_pos(new_x, new_y, game);
}

static void	move_left_right(t_game *game)
{
	double	perp_x;
	double	perp_y;
	double	new_x;
	double	new_y;

	perp_x = -game->player.dir_y;
	perp_y = game->player.dir_x;
	new_x = 0.0;
	new_y = 0.0;
	if (game->keys.a && !game->keys.d)
	{
		new_x = game->player.pos_x - perp_x * MOVEMENT_SPEED;
		new_y = game->player.pos_y - perp_y * MOVEMENT_SPEED;
	}
	if (game->keys.d && !game->keys.a)
	{
		new_x = game->player.pos_x + perp_x * MOVEMENT_SPEED;
		new_y = game->player.pos_y + perp_y * MOVEMENT_SPEED;
	}
	if (game->keys.a || game->keys.d)
		insert_valid_pos(new_x, new_y, game);
}

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
	move_forward_backward(game);
	move_left_right(game);
	rotate_camera(game);
}
