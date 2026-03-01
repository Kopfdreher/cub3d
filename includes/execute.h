/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:52:06 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/01 19:05:28 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "defines.h"

// Initialization
int		init_game_structs(t_game *game);
int		init_mlx_win(t_game *game);
int		load_textures(t_game *game);

// MLX
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// Game Loop & Render
int		render_next_frame(t_game *game);
void	draw_floor_and_ceiling(t_game *game);
void	cast_rays(t_game *game);

// Input Handling
int		key_press_handler(int keycode, t_game *game);
int		key_release_handler(int keycode, t_game *game);
int		close_window_handler(t_game *game);

// Movement
void	move_player(t_game *game);
void	rotate_camera(t_game *game, double rotation_speed);

// CleanUp
void	clean_up(t_game *game);

#endif
