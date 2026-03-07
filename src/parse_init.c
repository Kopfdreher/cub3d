/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:29:53 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/07 12:13:30 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*called from check_boarder_and_zero when we find a space character in the map, 
we want to make sure that it is not adjacent to any non-space characters,
check behind, in front, above, below, 
top left corner, top right corner, bottom left corner, bottom right corner
for a space character*/
static int	check_surrounding_spaces(t_config *config, int i, int j)
{
	if (config->map[i][j - 1] == ' ')
		return (FAILURE);
	if (config->map[i][j + 1] == ' ')
		return (FAILURE);
	if (config->map[i - 1][j] == ' ')
		return (FAILURE);
	if (config->map[i + 1][j] == ' ')
		return (FAILURE);
	if (config->map[i - 1][j - 1] == ' ')
		return (FAILURE);
	if (config->map[i - 1][j + 1] == ' ')
		return (FAILURE);
	if (config->map[i + 1][j - 1] == ' ')
		return (FAILURE);
	if (config->map[i + 1][j + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}

/*trim white spaces from the beginning and end of a string
	using ft_strtrim
ensure we could allocate memory for the trimmed string 
ensure that the trimmed string is not empty
if it is print an error message
return the trimmed string or NULL on error*/
static char	*trim_path_ws(char *original, int start_idx, char *label)
{
	char	*trimmed;

	trimmed = ft_strtrim(original + start_idx, " \t\n\r\v\f");
	if (!trimmed)
	{
		printf("Error: Could not allocate memory for %s texture path\n", label);
		return (NULL);
	}
	if (!*trimmed)
	{
		printf("Error: value is empty for %s\n", label);
		free(trimmed);
		return (NULL);
	}
	return (trimmed);
}

/* example of what it receives
set_config_path(&config->no_texture_path, line, i + 2, "NO"));
makes sure that we donta lready have something set for that path
if we do we skip white spaces and check if the path is empty after trimming, 
	if so we return failure 
*/
static int	set_config_path(char **target, char *line,
	int start_idx, char *label)
{
	if (*target != NULL)
	{
		printf("Error: Duplicate %s texture path\n", label);
		return (FAILURE);
	}
	*target = trim_path_ws(line, start_idx, label);
	if (*target == NULL)
		return (FAILURE);
	return (SUCCESS);
}

/*helper function to check if a character is valid in the map*/
static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == '\0' 
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*helper function to check if a character is a player character*/
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*sets the orientation values for the player based on their character*/
static void	set_player_orientation(t_player *player)
{

	if (player->player_char == 'N')
	{
		player->dir_y = -1.0;
		player->plane_x = 0.90;
	}
	else if (player->player_char == 'S')
	{
		player->dir_y = 1.0;
		player->plane_x = -0.90;
	}
	else if (player->player_char == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = 0.90;
	}
	else if (player->player_char == 'W')
	{
		player->dir_x = -1.0;
		player->plane_y = -0.90;
	}
}

/*called from valid_map
iterates through the map and checks if all characters are valid
	ex if it is a char we expect 
if we find a player char we check if we already have one, if so return failure
if not we set the player char and position and orientation values
check that we found a player char at the end and return failure if not
*/
static int	all_chars_valid(t_config *config, t_player *player, int i, int j)
{
	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if (!is_valid_map_char(config->map[i][j]))
				return (FAILURE);
			if (is_player_char(config->map[i][j]))
			{
				if (player->player_char != '\0')
					return (FAILURE);
				player->player_char = config->map[i][j];
				player->pos_x = (double)j + 0.5;
				player->pos_y = (double)i + 0.5;
				set_player_orientation(player);
			}
			j++;
		}
		i++;
	}
	if (player->player_char == '\0')
		return (FAILURE);
	return (SUCCESS);
}

/*called from check_boarder_and_zero
checks first and last rows for only 1s and spaces
checks left and right columns for 1s and spaces
if anything else found return failure*/
static int	check_boarders(t_config *config, int i, int j)
{
	if ((i == 0 || i == config->map_height - 1)
		&& config->map[i][j] != '1' && config->map[i][j] != ' ')
		return (FAILURE);
	if ((j == 0 || j == config->map_width - 1) 
		&& config->map[i][j] != '1' && config->map[i][j] != ' ')
		return (FAILURE);
	return (SUCCESS);
}
/*called from valid_map
skips white spaces
if we are have and empty line we break
sends to check_boarders and check_surrounding_spaces to ensure valid map*/
static int	check_boarder_and_zero(t_config *config, int i, int j)
{
	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			while (config->map[i][j] == ' ') //debating sending to ft_isspace
				j++;
			if (j >= config->map_width)
				break ;
			if (check_boarders(config, i, j) == FAILURE)
				return (FAILURE);
			if (config->map[i][j] == '0' || is_player_char(config->map[i][j]))
			{
				if (check_surrounding_spaces(config, i, j) == FAILURE)
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/*checks that the map is at least 3x3
uses helper to check if map only contains valid characters
uses helper to check boarders and zeros*/
int	valid_map(t_config *config, t_player *player)
{
	if (config->map_height < 3 || config->map_width < 3)
		return (FAILURE);
	if (all_chars_valid(config, player, 0, 0) == FAILURE)
		return (FAILURE);
	return (check_boarder_and_zero(config, 0, 0));
}

/*
checks for valid cub lines 
checks for white spaces 
checks for identifiers NO, SO etc
*/
int	parse_cub(char *line, t_config *config)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
	{
		i++;
		if (line[i] == '\0')
			return (SUCCESS);
	}
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (set_config_path(&config->no_texture_path, line, i + 2, "NO"));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (set_config_path(&config->so_texture_path, line, i + 2, "SO"));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (set_config_path(&config->we_texture_path, line, i + 2, "WE"));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (set_config_path(&config->ea_texture_path, line, i + 2, "EA"));
	else if (line[i] == 'F')
		return (set_config_path(&config->floor_str, line, i + 1, "F"));
	else if (line[i] == 'C')
		return (set_config_path(&config->ceiling_str, line, i + 1, "C"));
	return (FAILURE);
}

/*sets head and tail to the same node for the first node in the list*/
static void	set_a_b_to_c(t_list **a, t_list **b, t_list **c)
{
	*a = *c;
	*b = *c;
}

/*called from get_map_content
sets a new node with the line content and adds it to the end of the list
does a malloc check and if it fails clears the list and frees the line content 
	if we had already added a node to the list,
	otherwise just returns failure since we 
	didnt have anything to clear
sends to set_a_b_to_c to set head and tail if this is the first node, 
	otherwise just adds to the end and updates tail
*/
static int	add_nodes_to_list(char *line, t_list **head, t_list **tail)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node && !*head)
		return (FAILURE);
	if (!node)
		return (ft_lstclear(head, free), FAILURE);
	if (!*head)
		set_a_b_to_c(head, tail, &node);
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
	return (SUCCESS);
}

/*helper function to initialize the map list
also handles first line*/
static int	init_map_list(t_list **head, t_list **tail,
	char *first_line, t_config *config)
{
	t_list	*node;

	config->map_width = 0;
	*head = NULL;
	node = ft_lstnew(first_line);
	if (!node)
		return (free(first_line), FAILURE);
	set_a_b_to_c(head, tail, &node);
	config->map_width = ft_strlen(first_line);
	return (SUCCESS);
}

/*helper function to get the map content
sends to a helper function that initiates the map list and handles the first line
then reading line by line 
updates map width if the lin is the longest we have encountered
then sends to a helper to add nodes
then sets height of map to the number of lines read (nodes)
upon success returns the map content as a string array 
	having sent it to ft_lst_to_strarr_width*/
char	**get_map_content(int map_fd, char *first_line, t_config *config)
{
	t_list	*head;
	t_list	*tail;
	char	*line;

	if (init_map_list(&head, &tail, first_line, config) == FAILURE)
		return (NULL);
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		if (ft_strlen(line) > (size_t)config->map_width)
			config->map_width = ft_strlen(line);
		if (add_nodes_to_list(line, &head, &tail) == FAILURE)
			return (NULL);
	}
	config->map_height = ft_lstsize(head);
	return (ft_lst_to_strarr_width(&head, config->map_width));
}

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

/*receives the file descriptor and the first line of the map content
then sends to a helper function which reads the rest of the map content
closes fd on failure*/
static int	assign_map_content(t_config *config, int fd, char *line)
{
	config->map = get_map_content(fd, line, config);
	if (!config->map)
		return (close(fd), FAILURE);
	return (close(fd), SUCCESS);
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
