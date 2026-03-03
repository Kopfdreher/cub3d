/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:21:25 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/03 18:04:58 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, t_direction dir, char *path,
	char *dir_name)
{
	game->gfx.textures[dir].img = mlx_xpm_file_to_image(game->gfx.mlx,
			path, &game->gfx.textures[dir].width,
			&game->gfx.textures[dir].height);
	if (!game->gfx.textures[dir].img)
		return (printf("Error: Could not load %s texture from path: %s\n",
				dir_name, path), FAILURE);
	return (SUCCESS);
}

/* loads the 4 textures and stores them in the game struct, if any fail it 
returns failure and prints an error message with the path that failed and 
the direction it was trying to load for*/
int	parse_img(t_game *game)
{
	if (load_texture(game, NORTH, game->config.no_texture_path,
			"NORTH") == FAILURE)
		return (FAILURE);
	if (load_texture(game, EAST, game->config.ea_texture_path,
			"EAST") == FAILURE)
		return (FAILURE);
	if (load_texture(game, SOUTH, game->config.so_texture_path,
			"SOUTH") == FAILURE)
		return (FAILURE);
	if (load_texture(game, WEST, game->config.we_texture_path,
			"WEST") == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
