/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:16:57 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/05 16:06:58 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*this function frees all the memory allocated for the config structure */
int	free_parse(t_config *config)
{
	if (config->no_texture_path)
		free(config->no_texture_path);
	if (config->so_texture_path)
		free(config->so_texture_path);
	if (config->we_texture_path)
		free(config->we_texture_path);
	if (config->ea_texture_path)
		free(config->ea_texture_path);
	if (config->floor_str)
		free(config->floor_str);
	if (config->ceiling_str)
		free(config->ceiling_str);
	free_strarr(&config->map);
	config->no_texture_path = NULL;
	config->so_texture_path = NULL;
	config->we_texture_path = NULL;
	config->ea_texture_path = NULL;
	config->floor_str = NULL;
	config->ceiling_str = NULL;
	config->map = NULL;
	return (SUCCESS);
}

/*this function destroys all the loaded images and 
is called when closing window handler or when texture didnt load properly */
void	destroy_loaded_images(t_game *game)
{
	int	i;

	i = 0;
	if (!game)
		return ;
	while (i < 4)
	{
		if (game->gfx.mlx && game->gfx.textures[i].img)
			mlx_destroy_image(game->gfx.mlx, game->gfx.textures[i].img);
		ft_bzero(&game->gfx.textures[i], sizeof(t_img));
		i++;
	}
}

/*this is called when freeing the game structure mlx init functions didnt work*/
int	free_game(t_game *game)
{
	if (!game)
		return (SUCCESS);
	if (game->gfx.mlx && game->gfx.buff.img)
		mlx_destroy_image(game->gfx.mlx, game->gfx.buff.img);
	if (game->gfx.mlx && game->gfx.win)
		mlx_destroy_window(game->gfx.mlx, game->gfx.win);
	if (game->gfx.mlx)
		mlx_destroy_display(game->gfx.mlx);
	free(game->gfx.mlx);
	game->gfx.mlx = NULL;
	return (SUCCESS);
}
