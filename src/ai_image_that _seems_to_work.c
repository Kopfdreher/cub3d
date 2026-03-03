
#include "cub3d.h"

static void	destroy_loaded_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->gfx.textures[i].img)
		{
			mlx_destroy_image(game->gfx.mlx, game->gfx.textures[i].img);
			game->gfx.textures[i].img = NULL;
			game->gfx.textures[i].addr = NULL;
		}
		i++;
	}
}

static int	validate_texture_path(char *path, char *dir_name)
{
	int	fd;

	if (!path || !*path)
		return (printf("Error: Missing %s texture path\n", dir_name), FAILURE);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open %s texture: %s\n", dir_name, path),
			FAILURE);
	close(fd);
	return (SUCCESS);
}

static int	load_texture(t_game *game, t_direction dir, char *path,
	char *dir_name)
{
	char	*trimmed_path;

	trimmed_path = ft_strtrim(path, " \t\n\r\f\v");
	if (!trimmed_path)
		return (printf("Error: Could not allocate memory for %s texture path\n",
				dir_name), FAILURE);
	if (validate_texture_path(trimmed_path, dir_name) == FAILURE)
		return (free(trimmed_path), FAILURE);
	game->gfx.textures[dir].img = mlx_xpm_file_to_image(game->gfx.mlx,
			trimmed_path, &game->gfx.textures[dir].width,
			&game->gfx.textures[dir].height);
	if (!game->gfx.textures[dir].img)
	{
		printf("Error: Could not load %s texture from path: %s\n",
			dir_name, trimmed_path);
		free(trimmed_path);
		return (FAILURE);
	}
	if (game->gfx.textures[dir].width != TEXTURE_SIZE
		|| game->gfx.textures[dir].height != TEXTURE_SIZE)
	{
		mlx_destroy_image(game->gfx.mlx, game->gfx.textures[dir].img);
		game->gfx.textures[dir].img = NULL;
		printf("Error: %s texture must be %dx%d, got %dx%d (%s)\n",
				dir_name, TEXTURE_SIZE, TEXTURE_SIZE,
				game->gfx.textures[dir].width, game->gfx.textures[dir].height,
				trimmed_path);
		free(trimmed_path);
		return (FAILURE);
	}
	game->gfx.textures[dir].addr = mlx_get_data_addr(game->gfx.textures[dir].img,
			&game->gfx.textures[dir].bpp, &game->gfx.textures[dir].line_len,
			&game->gfx.textures[dir].endian);
	if (!game->gfx.textures[dir].addr)
	{
		mlx_destroy_image(game->gfx.mlx, game->gfx.textures[dir].img);
		game->gfx.textures[dir].img = NULL;
		printf("Error: Could not read %s texture pixels: %s\n",
			dir_name, trimmed_path);
		free(trimmed_path);
		return (FAILURE);
	}
	free(trimmed_path);
	return (SUCCESS);
}

/* loads the 4 textures and stores them in the game struct, if any fail it 
returns failure and prints an error message with the path that failed and 
the direction it was trying to load for*/
int	parse_img(t_game *game)
{
	if (load_texture(game, NORTH, game->config.no_texture_path,
			"NORTH") == FAILURE)
		return (destroy_loaded_textures(game), FAILURE);
	if (load_texture(game, EAST, game->config.ea_texture_path,
			"EAST") == FAILURE)
		return (destroy_loaded_textures(game), FAILURE);
	if (load_texture(game, SOUTH, game->config.so_texture_path,
			"SOUTH") == FAILURE)
		return (destroy_loaded_textures(game), FAILURE);
	if (load_texture(game, WEST, game->config.we_texture_path,
			"WEST") == FAILURE)
		return (destroy_loaded_textures(game), FAILURE);
	return (SUCCESS);
}
