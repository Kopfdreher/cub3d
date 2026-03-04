/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:06:11 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 21:33:42 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// mapping coordinates, initializing delta distances
static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ft_memset(ray, 0, sizeof(t_ray));
	ray->camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

// calculate step direction and initial distance
static void	calc_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = 
			(game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * 
			ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = 
			(game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * 
			ray->delta_dist_y;
	}
}

// exec dda then calc perpendicular distance
static void	execute_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->config.map_width ||
			ray->map_y < 0 || ray->map_y >= game->config.map_height)
			ray->hit = 1;
		else if (game->config.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

// calc wall_height and _pos and drawing it on buffer
static void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int	y;

	ray->line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
	ray->draw_start = SCREEN_HEIGHT / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = SCREEN_HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->side == 1)
		ray->color = 0x009381FF;
	else
		ray->color = 0x00B8B8FF;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(&game->gfx.buff, x, y, ray->color);
		y++;
	}
}

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		init_ray(game, &ray, x);
		calc_step(game, &ray);
		execute_dda(game, &ray);
		draw_wall(game, &ray, x);
	}
}
