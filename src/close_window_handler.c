/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:22:40 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 16:04:16 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window_handler(t_game *game)
{
	destroy_loaded_images(game);
	if (game->gfx.buff.img)
		mlx_destroy_image(game->gfx.mlx, game->gfx.buff.img);
	if (game->gfx.win)
		mlx_destroy_window(game->gfx.mlx, game->gfx.win);
	if (game->gfx.mlx)
		mlx_destroy_display(game->gfx.mlx);
	free(game->gfx.mlx);
	free_parse(&game->config);
	exit(SUCCESS);
	return (SUCCESS);
}
