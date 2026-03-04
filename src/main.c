/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:08:56 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/04 20:39:29 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_cub_file(char *arg, t_game *game)
{
	(void)arg;
	game->config.floor_color = 0xff160c28;
	game->config.ceiling_color = 0xffefcb68;
	game->config.map = malloc(sizeof(char *) * 6);
	game->config.map[0] = ft_strdup("11111");
	game->config.map[1] = ft_strdup("11011");
	game->config.map[2] = ft_strdup("10001");
	game->config.map[3] = ft_strdup("11011");
	game->config.map[4] = ft_strdup("11111");
	game->config.map[5] = NULL;
	game->player.pos_x = 2.5;
	game->player.pos_y = 2.5;
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.90;
	game->player.plane_y = 0.0;
	return (SUCCESS);
}

static void	init_hooks(t_game *game)
{
	mlx_hook(game->gfx.win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->gfx.win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->gfx.win, 17, 0, close_window_handler, game);
	mlx_loop_hook(game->gfx.mlx, render_next_frame, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error: Invalid Arg-Count\n"), 1);
	ft_memset(&game, 0, sizeof(t_game));
	if (parse_cub_file(argv[1], &game) == FAILURE)
		return (FAILURE);
	if (init_session(&game) == FAILURE)
	{
		// clean_exit_parser(&game, "Error: Failed MLX-Initialization\n");
		return (FAILURE);
	}
	init_hooks(&game);
	mlx_loop(game.gfx.mlx);
	return (SUCCESS);
}
