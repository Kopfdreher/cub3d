/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:56:12 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 20:56:42 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *game)
{
	if (parse_img(game) == FAILURE)
	{
		destroy_loaded_images(game);
		return (FAILURE);
	}
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
		return (free_game(game), FAILURE);
	game->gfx.buff.img = 
		mlx_new_image(game->gfx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->gfx.buff.img)
		return (free_game(game), FAILURE);
	game->gfx.buff.addr = 
		mlx_get_data_addr(game->gfx.buff.img, &game->gfx.buff.bpp,
			&game->gfx.buff.line_len, &game->gfx.buff.endian);
	if (!game->gfx.buff.addr)
		return (free_game(game), FAILURE);
	if (load_textures(game) == FAILURE)
		return (free_game(game), FAILURE);
	return (SUCCESS);
}
