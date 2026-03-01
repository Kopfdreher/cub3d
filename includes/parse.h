/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:59:04 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/01 16:02:51 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "defines.h"

int		parse_cub_file(char *filepath, t_game *game);

// Validation
int		check_file_extension(char *filepath);
int		validate_map_walls(t_data *dat);
int		extract_colors(char *line, t_data *data);
int		extract_textures(char *line, t_data *data);

// Memory Management
void	free_map(char **map);
void	clean_exit_parser(t_game *game, char *error_msg);

#endif
