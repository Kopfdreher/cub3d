/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:02:34 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 18:29:17 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling_floor(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				my_mlx_pixel_put(&game->gfx.buff,
					x, y, game->config.ceiling_color);
			else
				my_mlx_pixel_put(&game->gfx.buff,
					x, y, game->config.floor_color);
		}
	}
}

int		render_next_frame(t_game *game)
{
	move_player(game);
	put_ceiling_floor(game);
	cast_rays(game);
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.buff.img, 0, 0);
	return (SUCCESS);
}
