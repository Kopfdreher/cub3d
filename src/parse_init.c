/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:29:53 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/07 15:40:11 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*checks that a file was provided and tries to open it*/
static int	init_cub_errors(t_config *config, int *fd)
{
	if (!config->file_path)
	{
		printf("Error: No map file path provided\n");
		return (FAILURE);
	}
	*fd = open(config->file_path, O_RDONLY);
	if (*fd < 0)
	{
		printf("Error: Could not open file\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

/*helper function to skip leading whitespace.
returns ERROR if line is blank (only whitespace/newline), SUCCESS otherwise*/
static int	check_line_for_ws(char **line, int *i)
{
	*i = 0;
	while ((*line)[*i] == ' ' || (*line)[*i] == '\t')
		(*i)++;
	if ((*line)[*i] == '\n' || (*line)[*i] == '\0')
		return (ERROR);
	return (SUCCESS);
}

/*
sends to helper function that checks that a file was provided 
	and tries to open it
then using get_next_line to read the file line by line
skips blank lines and leading whitespace
if we encounter a line that starts with 1 or 0 
	we know we have reached the map content
so we send the fd and the first line (since its already read)
	to a helper function that reads the rest of the map content 
	into a string array and assigns it to the config struct
closes fd before returning failure 
only successfully returns if we were able to read the map content 
and assign it to the config struct
	implicitly returned by way of assign_map_content returning success
*/
int	open_cub(t_config *config)
{
	int		fd;
	char	*line;
	int		i;

	if (init_cub_errors(config, &fd) == FAILURE)
		return (FAILURE);
	line = get_next_line(fd);
	while ((line != NULL))
	{
		if (check_line_for_ws(&line, &i) == ERROR)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (line[i] == '1' || line[i] == '0')
			return (assign_map_content(config, fd, line));
		if (parse_cub(line, config) == FAILURE)
			return (free(line), close(fd), FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), FAILURE);
}

/*assign file path to the config struct
 sends to helper to check that a file was provided and can be opened
 checks that all required texture paths and color strings were provided 
	and that none are missing
then checks that we have a map to validate
and validates the map, checking for valid characters, valid boarders
	also ensures that 0s and player are properly enclosed by walls*/
int	parse_cub_file(char *filepath, t_game *game)
{
	int	i;

	game->config.file_path = filepath;
	i = open_cub(&game->config);
	if (i != 0)
		return (FAILURE);
	if (game->config.no_texture_path == NULL 
		|| game->config.so_texture_path == NULL 
		|| game->config.we_texture_path == NULL 
		|| game->config.ea_texture_path == NULL 
		|| game->config.floor_str == NULL 
		|| game->config.ceiling_str == NULL)
		return (printf("Error: Missing texture path or color\n"), FAILURE);
	if (game->config.map == NULL)
		return (printf("Error: Missing map in config file\n"), FAILURE);
	if (valid_map(&game->config, &game->player) == 1)
		return (printf("Error: Invalid map\n"), FAILURE);
	return (SUCCESS);
}

/*starts the parsing process
checks for cub extension
then does an initial parse of the file
finally converts color strings to integers*/
int	parse_init(char *filepath, t_game *game)
{
	if (valid_cub_extension(filepath) == FAILURE)
		return (FAILURE);
	if (parse_cub_file(filepath, game) == FAILURE)
		return (FAILURE);
	if (convert_color_str_to_int(&game->config) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
