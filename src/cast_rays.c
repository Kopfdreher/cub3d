/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:06:11 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 17:31:07 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_rays(t_game *game)
{
	int x = 0;

	while (x < SCREEN_WIDTH)
	{
		// 1.0 Setup the ray: calculate the angle of each pixel column
		double camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
		double ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		double ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

		// 1.1 which grid squaare is the player currently standing in
		int map_x = (int)game->player.pos_x;
		int map_y = (int)game->player.pos_y;

		// 1.2 How far the ray travels to cross exactly 1 grid square
		double delta_dist_x;
		double delta_dist_y;

		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1.0 / ray_dir_x);
		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1.0 / ray_dir_y);

		// 2.0 Caculate Initial Distance
		// which direction is the ray pointing at, and distance to the first gridline it will cross

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;
		int hit = 0; // hit a wall?
		int side; // which face of the wall did we hit? 0 = East/West, 1 = North/South

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
		}

		// 3.0 The DDA Algo
		// jump from gridline to gridline until we hit a '1'
		while (hit == 0)
		{
			// jump to the closest gridline
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->config.map[map_y][map_x] == '1')
				hit = 1;
		}

		// 4.0 Calculate perpendicular Distance
		double wall_dist;
		if (side == 0)
			wall_dist = (side_dist_x - delta_dist_x);
		else
			wall_dist = (side_dist_y - delta_dist_y);

		// 5.0 Draw the wall
		// how tall should the wall be?
		int line_height = (int)(SCREEN_HEIGHT / wall_dist);

		// Calculate the start and end pixels
		int draw_start = SCREEN_HEIGHT / 2 - line_height / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end = SCREEN_HEIGHT / 2 + line_height / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		// color the walls
		int color;

		if (side == 1)
			color = 0x00FF0000;
		else
			color = 0x00AA0000;

		// Paint the vertical line
		int y = draw_start;
		while (y < draw_end)
		{
			my_mlx_pixel_put(&game->gfx.buff, x, y, color);
			y++;
		}
		x++;
	}
}
