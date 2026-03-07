/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:06:11 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 14:21:55 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&game->gfx.textures[WEST]);
		else
			return (&game->gfx.textures[EAST]);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&game->gfx.textures[NORTH]);
		else
			return (&game->gfx.textures[SOUTH]);
	}
}

static double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

// calc tex_x and flip if mirrored
static void	draw_texture_stripe(t_game *game, t_ray *ray, t_img *tex, int x)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;

	tex_x = (int)(get_wall_x(game, ray) * (double)TEXTURE_SIZE);
	if ((ray->side == 0 && ray->dir_x < 0) || 
		(ray->side == 1 && ray->dir_y > 0))
		tex_x = TEXTURE_SIZE - tex_x - 1;
	step = ((double)TEXTURE_SIZE) / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + 
			ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
		tex_pos += step;
		ray->color = *(unsigned int *)(tex->addr + 
				(tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
		my_mlx_pixel_put(&game->gfx.buff, x, y, ray->color);
		y++;
	}
}

// calc wall_height and _pos and drawing it on buffer
static void	draw_wall(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;

	ray->line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
	ray->draw_start = SCREEN_HEIGHT / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = SCREEN_HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	tex = get_texture(game, ray);
	draw_texture_stripe(game, ray, tex, x);
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
