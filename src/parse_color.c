/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:17:25 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/03 16:33:30 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cf_strarr(char **floor_colors, char **ceiling_colors,
	char *error_msg)
{
	if (error_msg)
		printf("%s", error_msg);
	free_strarr(&ceiling_colors);
	free_strarr(&floor_colors);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

//this checks that the color string contains at least one digit, and that all non-space characters are digits
int	ft_isdigit_in_str(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (ft_isdigit((int)str[j]))
			return (SUCCESS);
		j++;
	}
	return (FAILURE);
}

//this checks that all non-space characters in the color string are digits, this is to catch cases like "F: 255, 255, 255f"
int	ft_is_only_digit_str(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		while (str[j] && ft_isspace(str[j]))
			j++;
		if (!str[j])
			break ;
		if (!ft_isdigit((int)str[j]))
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	color_count_check(char **floor_colors, char **ceiling_colors)
{
	int		i;
	int		j;

	i = 0;
	while (floor_colors[i])
	{
		//check that each color string contains at least one digit
			//this is to catch cases like "F: 255, , 255" where the middle color is missing but we still have 3 color strings
		if (ft_isdigit_in_str(floor_colors[i]) == FAILURE)
			return (FAILURE);
		if (ft_is_only_digit_str(floor_colors[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	j = 0;
	while (ceiling_colors[j])
	{
		if (ft_isdigit_in_str(ceiling_colors[j]) == FAILURE)
			return (FAILURE);
		if (ft_is_only_digit_str(ceiling_colors[j]) == FAILURE)
			return (FAILURE);
		j++;
	}
	if (i != 3 || j != 3)
		return (FAILURE);
	return (SUCCESS);
}

int	convert_colors(t_config *config, char **floor_colors,
	char **ceiling_colors)
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
	config->floor_color = (r << 16) | (g << 8) | b;
	r = ft_atoi(ceiling_colors[0]);
	g = ft_atoi(ceiling_colors[1]);
	b = ft_atoi(ceiling_colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_cf_strarr(floor_colors, ceiling_colors, 
				"Error: Color values must be between 0 and 255\n"), FAILURE);
	config->ceiling_color = (r << 16) | (g << 8) | b;
	return (free_cf_strarr(floor_colors, ceiling_colors, NULL), SUCCESS);
}

int count_commas(char *str)
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

int	convert_color_str_to_int(t_config *config)
{
	char	**floor_colors;
	char	**ceiling_colors;

	if (count_commas(config->floor_str) != 2 || count_commas(config->ceiling_str) != 2)
		return (printf("Error: Invalid color format, must contain exactly 2 commas\n"), FAILURE);	
	floor_colors = ft_split(config->floor_str, ',');
	ceiling_colors = ft_split(config->ceiling_str, ',');
	if (!floor_colors || !ceiling_colors)
		return (free_cf_strarr(floor_colors, ceiling_colors,
				"Error: Could not allocate memory for color strings\n"),
			FAILURE);
	if (floor_colors && *floor_colors && ceiling_colors && *ceiling_colors)
	{
		if (color_count_check(floor_colors, ceiling_colors) == FAILURE)
			return (free_cf_strarr(floor_colors, ceiling_colors,
					"Error: Invalid color format\n"), FAILURE);
	}
	return (convert_colors(config, floor_colors, ceiling_colors));
}
