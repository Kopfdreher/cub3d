/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all_chars_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:11:34 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 13:57:58 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*helper function to check if a character is valid in the map*/
static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == '\0' 
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*helper function to check if a character is a player character*/
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*sets the orientation values for the player based on their character*/
static void	set_player_orientation(t_player *player)
{
	if (player->player_char == 'N')
	{
		player->dir_y = -1.0;
		player->plane_x = PLANE;
	}
	else if (player->player_char == 'S')
	{
		player->dir_y = 1.0;
		player->plane_x = -PLANE;
	}
	else if (player->player_char == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = PLANE;
	}
	else if (player->player_char == 'W')
	{
		player->dir_x = -1.0;
		player->plane_y = -PLANE;
	}
}

/*called from valid_map
iterates through the map and checks if all characters are valid
	ex if it is a char we expect 
if we find a player char we check if we already have one, if so return failure
if not we set the player char and position and orientation values
check that we found a player char at the end and return failure if not
*/
int	all_chars_valid(t_config *config, t_player *player, int i, int j)
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
