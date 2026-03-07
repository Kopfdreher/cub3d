/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:48:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 10:37:04 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_pos(t_game *game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)x;
	grid_y = (int)y;
	if (grid_x < 0 || grid_x >= game->config.map_width ||
		grid_y < 0 || grid_y >= game->config.map_height)
		return (FALSE);
	if (!game->config.map[grid_y])
		return (FALSE);
	if (game->config.map[grid_y][grid_x] == '1' ||
		game->config.map[grid_y][grid_x] == ' ')
		return (FALSE);
	return (TRUE);
}

static void	insert_valid_pos(double new_x, double new_y, t_game *game)
{
	double	buffer_x;
	double	buffer_y;

	buffer_x = 0.2;
	if (new_x < game->player.pos_x)
		buffer_x = -0.2;
	buffer_y = 0.2;
	if (new_y < game->player.pos_y)
		buffer_y = -0.2;
	if (is_valid_pos(game, new_x + buffer_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_pos(game, game->player.pos_x, new_y + buffer_y))
		game->player.pos_y = new_y;
}

static void	set_movement(double move[2], double x, double y)
{
	move[X] += x;
	move[Y] += y;
}

static void	calc_movement(t_game *game)
{
	double	move[2];
	double	perp[2];

	move[X] = 0.0;
	move[Y] = 0.0;
	perp[X] = -game->player.dir_y;
	perp[Y] = game->player.dir_x;
	if (game->keys.w)
		set_movement(move, game->player.dir_x * MOVEMENT_SPEED, 
			game->player.dir_y * MOVEMENT_SPEED);
	if (game->keys.s)
		set_movement(move, game->player.dir_x * -MOVEMENT_SPEED, 
			game->player.dir_y * -MOVEMENT_SPEED);
	if (game->keys.a)
		set_movement(move, perp[X] * -MOVEMENT_SPEED, 
			perp[Y] * -MOVEMENT_SPEED);
	if (game->keys.d)
		set_movement(move, perp[X] * MOVEMENT_SPEED, 
			perp[Y] * MOVEMENT_SPEED);
	if (move[X] != 0.0 || move[Y] != 0.0)
		insert_valid_pos(game->player.pos_x + move[X], 
			game->player.pos_y + move[Y], game);
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
	calc_movement(game);
	rotate_camera(game);
}
