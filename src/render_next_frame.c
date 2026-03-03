/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:02:34 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 15:15:44 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_next_frame(t_game *game)
{
	mlx_put_image_to_window(game->gfx.mlx, game->gfx.win, game->gfx.buff.img, 0, 0);
	return (SUCCESS);
}
