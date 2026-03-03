/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:16:57 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/03 15:16:58 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_parse(t_config *config)
{
	if (config->no_texture_path)
		free(config->no_texture_path);
	if (config->so_texture_path)
		free(config->so_texture_path);
	if (config->we_texture_path)
		free(config->we_texture_path);
	if (config->ea_texture_path)
		free(config->ea_texture_path);
	if (config->floor_str)
		free(config->floor_str);
	if (config->ceiling_str)
		free(config->ceiling_str);
	free_strarr(&config->map);
	config->no_texture_path = NULL;
	config->so_texture_path = NULL;
	config->we_texture_path = NULL;
	config->ea_texture_path = NULL;
	config->floor_str = NULL;
	config->ceiling_str = NULL;
	config->map = NULL;
	return (SUCCESS);
}
