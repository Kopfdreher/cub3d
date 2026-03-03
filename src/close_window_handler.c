/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:22:40 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 16:59:31 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window_handler(t_game *game)
{
	if (game->gfx.buff.img)
		mlx_destroy_image(game->gfx.mlx, game->gfx.buff.img);
	if (game->gfx.win)
		mlx_destroy_window(game->gfx.mlx, game->gfx.win);
	if (game->gfx.mlx)
		mlx_destroy_display(game->gfx.mlx);
	free(game->gfx.mlx);
	// free_parse();
	free(game->config.map[0]);
	free(game->config.map[1]);
	free(game->config.map[2]);
	free(game->config.map[3]);
	free(game->config.map[4]);
	free(game->config.map);
	exit(SUCCESS);
	return (SUCCESS);
}
