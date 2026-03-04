/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:59:04 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 18:40:59 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "defines.h"

//init
int parse_init(char *filepath, t_game *game);

int		parse_cub_file(char *filepath, t_game *game);
int convert_color_str_to_int(t_config *config);
char	**ft_lst_to_strarr_width(t_list **lst, int width);
int	parse_img(t_game *game);
//free
int free_parse(t_config *config);

//helpers
int	ft_isspace(char c);

// Validation
int	valid_cub_extension(char *filepath);
int	valid_xpm_extension(char *filepath);

int		check_file_extension(char *filepath);
int		extract_colors(char *line, t_game *game);
int		extract_textures(char *line, t_game *game);
int		validate_map_walls(t_game *game);

// Memory Management
void	free_map(char **map);
void	clean_exit_parser(t_game *game, char *error_msg);

#endif
