/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:21:25 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/06 12:55:05 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*helper function to check if the texture path is valid, 
can be opened and is actually an xpm file*/
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

/*helper function to load a texture
checks if the texture path is valid, can be opened and is actually an xpm file
if so load the texture using mlx_xpm_file_to_image
check if actaully loaded texture 
check dimensions */
static int	load_texture(t_game *game, t_dir dir, char *path,
	char *dir_name)
{
	if (check_texture_path(path) == FAILURE)
		return (FAILURE);
	game->gfx.textures[dir].img = mlx_xpm_file_to_image(game->gfx.mlx,
			path, &game->gfx.textures[dir].width,
			&game->gfx.textures[dir].height);
	if (!game->gfx.textures[dir].img)
		return (printf("Error: Could not load %s texture from path: %s\n",
				dir_name, path), FAILURE);
	if (game->gfx.textures[dir].width != TEXTURE_SIZE
		|| game->gfx.textures[dir].height != TEXTURE_SIZE)
		return (printf("Error: Texture %s dimensions invalid, expected %dx%d\n",
				path, TEXTURE_SIZE, TEXTURE_SIZE), FAILURE);
	game->gfx.textures[dir].addr = 
		mlx_get_data_addr(game->gfx.textures[dir].img, 
			&game->gfx.textures[dir].bpp, &game->gfx.textures[dir].line_len,
			&game->gfx.textures[dir].endian);
	if (!game->gfx.textures[dir].addr)
		return (printf("Error: Texture address of %s invalid\n", path), FAILURE);
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
