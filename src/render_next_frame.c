/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:02:34 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 09:43:39 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_ceiling_floor(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < SCREEN_HEIGHT / 2)
				my_mlx_pixel_put(&game->gfx.buff,
					x, y, game->config.u_ceiling_color.color);
			else
				my_mlx_pixel_put(&game->gfx.buff,
					x, y, game->config.u_floor_color.color);
		}
	}
}

static long long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	render_next_frame(t_game *game)
{
	long long curr_time;

	curr_time = get_time_in_ms();
	if (curr_time - game->gfx.last_frame_time < 20)
		return (SUCCESS);
	game->gfx.last_frame_time = curr_time;
	move_player(game);
	put_ceiling_floor(game);
	cast_rays(game);
	mlx_put_image_to_window(game->gfx.mlx,
		game->gfx.win, game->gfx.buff.img, 0, 0);
	return (SUCCESS);
}
