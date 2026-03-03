/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:08:56 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 14:22:08 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_cub_file(char *arg, t_game *game)
{
	(void)arg;
	(void)game;
	return (SUCCESS);
}

/*
void	init_hooks(t_game *game)
{
	mlx_hook(game->gfx.win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->gfx.win, 3, 1L << 0, key_release_handler, game);
	mlx_hook(game->gfx.win, 17, 0, close_window_handler, game);
	mlx_loop_hook(game->gfx.mlx, render_next_frame, game);
}
*/

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
	/*
	init_hooks(*game);
	mlx_loop(game.gfx.mlx);
	clean_up(&game);
	*/
	return (SUCCESS);
}
