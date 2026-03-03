/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:29:53 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/03 16:50:51 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_surrounding_spaces(t_config *config, int i, int j);

//copilot broke this out so that I dont have reapeat code
static int	set_config_path(char **target, char *line,
	int start_idx, char *label)
{
	if (*target != NULL)
	{
		printf("Error: Duplicate %s texture path\n", label);
		return (FAILURE);
	}
	*target = ft_strdup(line + start_idx);
	if (*target == NULL)
	{
		printf("Error: Could not allocate memory for %s texture path\n", label);
		return (FAILURE);
	}
	return (SUCCESS);
}

// Ignore all leading whitespaces.
// If the current row is the 0th row or the final row, 
//	only accept '1's and ' 's.
// else, The first and final character should always be a '1'.
// In the case of any non leading whitespaces, the only acceptable characters 
// 	adjacent to the space are '1's or ' 's.
// if strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top)
// 	current character should be '1'
// If strlen(curr_row) > strlen(row_on_bottom) && 
// 	current col > strlen(row_on_bottom), current character should be '1'
// copilot was filling some of this in but I made sure to understand it and 
// 	that it followed the map requirements, so I kept it. I also added some 
//	additional checks to make sure we have a map to validate and that we skip 
//		leading whitespace before checking the other conditions.0
/*we first check to make sure all chars are valid and only 1 player char*/
/* I keep the player char in place so that we can check it for validity 
and then use it later when we initialize the player struct */
/*	while (i < config->map_height) // then check to make sure the map is valid*/
int valid_map(t_config *config, t_player *player)
{
	int	i;
	int	j;

	i = 0;

	if (config->map_height < 3 || config->map_width < 3)
		return (FAILURE);
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if (config->map[i][j] != '1' && config->map[i][j] != '0' 
				&& config->map[i][j] != ' ' && config->map[i][j] != '\0' 
				&& config->map[i][j] != 'N' && config->map[i][j] != 'S' 
				&& config->map[i][j] != 'E' && config->map[i][j] != 'W')
				return (FAILURE);
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S' 
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				if (player->player_char != '\0')
					return (FAILURE);
				player->player_char = config->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (player->player_char == '\0')
		return (FAILURE);
	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			while (config->map[i][j] == ' ')
				j++;
			if (j >= config->map_width)
				break ;
			if ((i == 0 || i == config->map_height - 1)
				&& config->map[i][j] != '1' && config->map[i][j] != ' ')
				return (FAILURE);
			if ((j == 0 || j == config->map_width - 1) 
				&& config->map[i][j] != '1' && config->map[i][j] != ' ')
				return (FAILURE);
			if (config->map[i][j] == '0' || config->map[i][j] == 'N' 
				|| config->map[i][j] == 'S' || config->map[i][j] == 'E' 
				|| config->map[i][j] == 'W')
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

/*check behind, in front, above, below, 
top left corner, top right corner, bottom left corner, bottom right corner*/
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

// int valid_map(t_game *game)
// {
//     int i;
//     int j;

//     if (game->height < 3 || game->width < 3)
//         return (FAILURE);
//     i = 0;
//     while (i < game->height)
//     {
//         j = 0;
//         while (j < game->width)
//         {
//             while (game->map[i][j] == ' ')
//                 j++;
//             if (j >= game->width)
//                 break ;
//             if ((i == 0 || i == game->height - 1)
//                 && game->map[i][j] != '1' && game->map[i][j] != ' ')
//                 return (FAILURE);
//             if ((j == 0 || j == game->width - 1) && game->map[i][j] != '1')
//                 return (FAILURE);
//             if (game->map[i][j] == ' ')
//             {
//                 if (game->map[i][j - 1] != '1' && game->map[i][j - 1] != ' ')
//                     return (FAILURE);
//                 if (game->map[i][j + 1] != '1' && game->map[i][j + 1] != ' ')
//                     return (FAILURE);
//                 if ((i > 0 && (game->map[i - 1][j] != '1' && game->map[i - 1][j] != ' '))
//                     || (i < game->height - 1
//                     && (game->map[i + 1][j] != '1' && game->map[i + 1][j] != ' ')))
//                     return (FAILURE);
//             }
//             if (i > 0 && ft_strlen(game->map[i]) > ft_strlen(game->map[i - 1])
//                 && j > (int)ft_strlen(game->map[i - 1]) && game->map[i][j] != '1')
//                 return (FAILURE);
//             if (i < game->height - 1 && ft_strlen(game->map[i]) > ft_strlen(game->map[i + 1])
//                 && j > (int)ft_strlen(game->map[i + 1]) && game->map[i][j] != '1')
//                 return (FAILURE);
//             j++;
//         }
//         i++;
//     }
//     return (SUCCESS);
// }

//step 1
//store the values so that we can use them later
//step 2

int	parse_cub(char *line, t_config *config)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
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

static void	set_a_b_to_c(t_list **a, t_list **b, t_list **c)
{
	*a = *c;
	*b = *c;
}

char	**get_map_content(int map_fd, char *first_line, t_config *config)
{
	t_list	*head;
	t_list	*tail;
	t_list	*node;
	char	*line;

	config->map_width = 0;
	head = NULL;
	node = ft_lstnew(first_line);
	if (!node)
		return (free(first_line), NULL);
	set_a_b_to_c(&head, &tail, &node);
	config->map_width = ft_strlen(first_line);
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		if (ft_strlen(line) > (size_t)config->map_width)
			config->map_width = ft_strlen(line);
		node = ft_lstnew(line);
		if (!node && !head)
			return (NULL);
		if (!node)
			return (ft_lstclear(&head, free), NULL);
		if (!head)
			set_a_b_to_c(&head, &tail, &node);
		else
		{
			tail->next = node;
			tail = node;
		}
	}
	config->map_height = ft_lstsize(head);
	return (ft_lst_to_strarr_width(&head, config->map_width));
}

int	open_cub(t_config *config)
{
	int		fd;
	char	*line;
	int		i;

	if (!config->file_path)
	{
		printf("Error: No map file path provided\n");
		return (FAILURE);
	}
	fd = open(config->file_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Could not open file\n");
		return (FAILURE);
	}
	line = get_next_line(fd);
	while ((line != NULL))
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (line[i] == '1' || line[i] == '0')
		{
			config->map = get_map_content(fd, line, config);
			if (!config->map)
				return (close(fd), FAILURE);
			return (close(fd), SUCCESS);
		}
		if (parse_cub(line, config) == FAILURE)
			return (free(line), close(fd), FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (FAILURE);
}

/*after we check for files being there we check for validity of map*/
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
	if (convert_color_str_to_int(&game->config) == FAILURE)
		return (printf("Error: Invalid color\n"), FAILURE);
	return (SUCCESS);
}
