/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:40:49 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 12:40:55 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*helper function to free the color string arrays and print an error message*/
void	free_cf_strarr(char **floor_colors, char **ceiling_colors,
	char *error_msg)
{
	if (error_msg)
		printf("%s", error_msg);
	free_strarr(&ceiling_colors);
	free_strarr(&floor_colors);
}

/*helper function to check if a string contains 
only digits and white spaces
checks end for white spaces
if no digits found, return FAILURE 
if havent reached end after possible white spaces, 
definitive digits and possible trailing spaces, return FAILURE*/
int	ft_is_only_digit_str(char *str)
{
	int	j;
	int	digit_found;

	j = 0;
	digit_found = 0;
	while (str[j] && ft_isspace(str[j]))
		j++;
	while (str[j] && ft_isdigit((int)str[j]))
	{
		digit_found = 1;
		j++;
	}
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (!digit_found || str[j] != '\0')
		return (FAILURE);
	return (SUCCESS);
}
