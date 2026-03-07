/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:21:31 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 13:21:42 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
