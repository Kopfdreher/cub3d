/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:21:25 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/05 12:58:36 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	check_texture_path(char *path)
{
	int	fd;

	if (!path || !*path)
		return (printf("Error: Texture path is empty\n"), FAILURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error: unable to open texture file %s\n", path),
			FAILURE);
	close(fd);
	if (valid_xpm_extension(path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	load_texture(t_game *game, t_direction dir, char *path,
	char *dir_name)
{
	//first make sure that the texture paths are valid and can be opened and is actually and xpm file
	if (check_texture_path(path) == FAILURE)
		return (FAILURE);
	//if so then load
	game->gfx.textures[dir].img = mlx_xpm_file_to_image(game->gfx.mlx,
			path, &game->gfx.textures[dir].width,
			&game->gfx.textures[dir].height);
	//once we load we need to check if actaully loaded texture and if it has the right dimensions
	if (!game->gfx.textures[dir].img)
		return (printf("Error: Could not load %s texture from path: %s\n",
				dir_name, path), FAILURE);
	if (game->gfx.textures[dir].width != TEXTURE_SIZE
		|| game->gfx.textures[dir].height != TEXTURE_SIZE)
		return (printf("Error: Texture %s dimensions invalid, expected %dx%d\n",
				path, TEXTURE_SIZE, TEXTURE_SIZE), FAILURE);
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
