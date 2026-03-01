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


int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (printf("Error: Invalid Arg-Count\n"), 1);
	ft_memset(&game, 0, sizeof(t_game));
	if (parse_cub_file(argv[1], &game) == FAILURE)
		return (FAILURE);
	/*
	if (init_mlx_win(&game) == FAILURE)
		return (FAILURE);
	mlx_loop_hook(game.gfx.mlx, render_next_frame, &game);
	mlx_loop(game.gfx.mlx);
	*/
	return (SUCCESS);
}
