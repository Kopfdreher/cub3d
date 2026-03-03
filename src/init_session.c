/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:56:12 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 15:57:32 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_textures(t_game *game)
{
	(void)game;
	return (SUCCESS);
}

int	init_session(t_game *game)
{
	game->gfx.mlx = mlx_init();
	if (!game->gfx.mlx)
		return (FAILURE);
	game->gfx.win =
		mlx_new_window(game->gfx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->gfx.win)
	{
		mlx_destroy_display(game->gfx.mlx);
		free(game->gfx.mlx);
		return (FAILURE);
	}
	game->gfx.buff.img =
		mlx_new_image(game->gfx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->gfx.buff.addr =
		mlx_get_data_addr(game->gfx.buff.img, &game->gfx.buff.bpp,
			&game->gfx.buff.line_len, &game->gfx.buff.endian);
	if (load_textures(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

