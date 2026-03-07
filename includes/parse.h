/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:59:04 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 13:24:59 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "defines.h"

//init
int		parse_init(char *filepath, t_game *game);

int		parse_cub(char *line, t_config *config);
int		parse_cub_file(char *filepath, t_game *game);
int		convert_color_str_to_int(t_config *config);
char	**ft_lst_to_strarr_width(t_list **lst, int width);
int		parse_img(t_game *game);
int		assign_map_content(t_config *config, int fd, char *line);

//free
int		free_parse(t_config *config);

//helpers
int		ft_isspace(char c);

//color_helpers
void	free_cf_strarr(char **floor_colors, char **ceiling_colors, 
			char *error_msg);
int		ft_is_only_digit_str(char *str);

// Validation
int		valid_cub_extension(char *filepath);
int		valid_xpm_extension(char *filepath);

int		check_file_extension(char *filepath);
int		extract_colors(char *line, t_game *game);
int		extract_textures(char *line, t_game *game);
int		valid_map(t_config *config, t_player *player);
int		validate_map_walls(t_game *game);

//parse_all_char_valid
int		all_chars_valid(t_config *config, t_player *player, int i, int j);
int		is_player_char(char c);

// Memory Management
void	free_map(char **map);
void	clean_exit_parser(t_game *game, char *error_msg);

#endif
