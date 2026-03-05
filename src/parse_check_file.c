/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:12:11 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/03 17:20:24 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_cub_extension(char *filepath)
{
	int	len;

	len = ft_strlen(filepath);
	if (len < 4 || ft_strncmp(filepath + len - 4, ".cub", 4) != 0)
		return (printf("Error: Invalid file extension, expected .cub\n"),
			FAILURE);
	return (SUCCESS);
}

int	valid_xpm_extension(char *filepath)
{
	int	len;

	len = ft_strlen(filepath);
	if (len < 4 || ft_strncmp(filepath + len - 4, ".xpm", 4) != 0)
		return (printf("Error: Invalid file extension, expected .xpm\n"),
			FAILURE);
	return (SUCCESS);
}
