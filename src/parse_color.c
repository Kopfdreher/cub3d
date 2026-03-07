/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:17:25 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/07 15:30:28 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*checks if the number of color values is correct
sends to helper to look for only digits
and ensures that exactly 3 color values are provided*/
int	validate_color_components(char **floor_colors, char **ceiling_colors)
{
	int		i;
	int		j;

	i = 0;
	while (floor_colors[i])
	{
		if (ft_is_only_digit_str(floor_colors[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	j = 0;
	while (ceiling_colors[j])
	{
		if (ft_is_only_digit_str(ceiling_colors[j]) == FAILURE)
			return (FAILURE);
		j++;
	}
	if (i != 3 || j != 3)
		return (FAILURE);
	return (SUCCESS);
}

/*helper function to convert color strings to integers
first uses ft_atoi to convert each color string to an integer
then checks if the values are within the valid range 
then assigns the values to the config structure UNION
repeats for floor and ceiling colors
frees the color string arrays before returning*/
int	convert_colors(t_config *config, char **floor_colors, char **ceiling_colors)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(floor_colors[0]);
	g = ft_atoi(floor_colors[1]);
	b = ft_atoi(floor_colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_cf_strarr(floor_colors, ceiling_colors,
				"Error: Color values must be between 0 and 255\n"), FAILURE);
	config->u_floor_color.rgb.r = (unsigned char)r;
	config->u_floor_color.rgb.g = (unsigned char)g;
	config->u_floor_color.rgb.b = (unsigned char)b;
	r = ft_atoi(ceiling_colors[0]);
	g = ft_atoi(ceiling_colors[1]);
	b = ft_atoi(ceiling_colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_cf_strarr(floor_colors, ceiling_colors,
				"Error: Color values must be between 0 and 255\n"), FAILURE);
	config->u_ceiling_color.rgb.r = (unsigned char)r;
	config->u_ceiling_color.rgb.g = (unsigned char)g;
	config->u_ceiling_color.rgb.b = (unsigned char)b;
	return (free_cf_strarr(floor_colors, ceiling_colors, NULL), SUCCESS);
}

// counts commas in a string
int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

/*
 * ensures we have exactly 2 commas in each color string
 * splits the color strings on commas completes malloc check
 * then checks color components for validity (only digits, 
 * no extra characters, exactly 3 components) then converts 
 * the color strings to integers and assigns to config structure
*/
int	convert_color_str_to_int(t_config *config)
{
	char	**floor_colors;
	char	**ceiling_colors;

	if (count_commas(config->floor_str) != 2 
		|| count_commas(config->ceiling_str) != 2)
	{
		printf("Error: Invalid color format, must contain exactly 2 commas\n");
		return (FAILURE);
	}
	floor_colors = ft_split(config->floor_str, ',');
	ceiling_colors = ft_split(config->ceiling_str, ',');
	if (!floor_colors || !ceiling_colors)
		return (free_cf_strarr(floor_colors, ceiling_colors,
				"Error: Could not allocate memory for color strings\n"),
			FAILURE);
	if (floor_colors && *floor_colors && ceiling_colors && *ceiling_colors)
	{
		if (validate_color_components(floor_colors, ceiling_colors) == FAILURE)
			return (free_cf_strarr(floor_colors, ceiling_colors,
					"Error: Invalid color format\n"), FAILURE);
	}
	return (convert_colors(config, floor_colors, ceiling_colors));
}
