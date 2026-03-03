/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:08:56 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 17:17:40 by aabelkis         ###   ########.fr       */
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
	printf("colors: floor: %x, ceiling: %x\n", game->config.floor_color, game->config.ceiling_color);
	printf("map:\n");
	i = 0;
	while (game->config.map && game->config.map[i])
	{
		printf("%s\n", game->config.map[i]);
		i++;
	}
}

/*
void	init_hooks(t_game *game)
{
	mlx_hook(game->gfx.win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->gfx.win, 3, 1L << 0, key_release_handler, game);
	mlx_hook(game->gfx.win, 17, 0, close_window_handler, game);
}
*/

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error: Invalid Arg-Count\n"), FAILURE);
	ft_memset(&game, 0, sizeof(t_game));
	if (parse_init(argv[1], &game) == FAILURE)
		return (free_parse(&game.config), FAILURE);
	print_config_debug(&game);
	if (init_session(&game) == FAILURE)
		return (free_parse(&game.config), FAILURE);

	mlx_hook(game.gfx.win, 2, 1L << 0, key_press_handler, &game);
	mlx_hook(game.gfx.win, 17, 0, close_window_handler, &game);
	mlx_loop_hook(game.gfx.mlx, render_next_frame, &game);
	// init_hooks(*game);
	mlx_loop(game.gfx.mlx);
	return (free_parse(&game.config), SUCCESS);
}