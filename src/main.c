/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:08:56 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/01 16:57:32 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_config_debug(t_game *game)
{
	int	i;

	printf("--- Parsed Config ---\n");
	printf("file_path: %s\n", game->config.file_path);
	printf("NO: %s\n", game->config.no_texture_path);
	printf("SO: %s\n", game->config.so_texture_path);
	printf("WE: %s\n", game->config.we_texture_path);
	printf("EA: %s\n", game->config.ea_texture_path);
	printf("F: %s\n", game->config.floor_str);
	printf("C: %s\n", game->config.ceiling_str);
	printf("map_width: %d\n", game->config.map_width);
	printf("map_height: %d\n", game->config.map_height);
	printf("player_char: %c\n", game->player.player_char);
	printf("map:\n");
	i = 0;
	while (game->config.map && game->config.map[i])
	{
		printf("%s\n", game->config.map[i]);
		i++;
	}
}


int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error: Invalid Arg-Count\n"), FAILURE);
	ft_memset(&game, 0, sizeof(t_game));
	if (parse_cub_file(argv[1], &game) == FAILURE)
		return (free_parse(&game.config), FAILURE);
	print_config_debug(&game);
	/* 
	need to init mlx bfore I can work with textures
	if (init_mlx_win(&game) == FAILURE)
		return (FAILURE);
	mlx_loop_hook(game.gfx.mlx, render_next_frame, &game);
	mlx_loop(game.gfx.mlx);
	*/
	return (free_parse(&game.config), SUCCESS);
}
