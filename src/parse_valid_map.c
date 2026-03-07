/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:16:42 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 13:17:22 by sgavrilo         ###   ########.fr       */
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

/*
 * called from valid_map skips white spaces if we are have and empty line 
 * we break sends to check_boarders and check_surrounding_spaces to ensure 
 * valid map
*/
static int	check_boarder_and_zero(t_config *config, int i, int j)
{
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
