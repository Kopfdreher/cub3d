/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_starr_width.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:51:18 by aabelkis          #+#    #+#             */
/*   Updated: 2026/03/03 15:47:44 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**insert_content(t_list **lst, char **strarr, int width, int i)
{
	char	*content;
	int		j;

	content = (char *)(*lst)->content;
	strarr[i] = malloc(sizeof(char) * (width + 1));
	if (!strarr[i])
	{
		while (i > 0)
			free(strarr[--i]);
		free(strarr);
		return (ft_lstclear(lst, free), NULL);
	}
	j = 0;
	while (j < width && content[j] && content[j] != '\n')
	{
		strarr[i][j] = content[j];
		j++;
	}
	while (j < width)
		strarr[i][j++] = ' ';
	strarr[i][width] = '\0';
	return (free (content), strarr);
}

static void	init_strarr(t_list **lst, int width, int *lst_size, char ***strarr)
{
	if (width < 0)
		width = 0;
	*lst_size = ft_lstsize(*lst);
	*strarr = malloc(sizeof(char *) * (*lst_size + 1));
}
/*Allocates and pads strings to width
Stops at newline when encountered
Frees list nodes and handles errors properly
Cleans up on failure cases*/
char	**ft_lst_to_strarr_width(t_list **lst, int width)
{
	//copilot filled this in but I fully understand it
	int		lst_size;
	t_list	*next;
	int		i;
	char	**strarr;

	init_strarr(lst, width, &lst_size, &strarr);
	if (!strarr)
		return (ft_lstclear(lst, free), NULL);
	i = 0;
	while (*lst)
	{
		next = (*lst)->next;
		if (!insert_content(lst, strarr, width, i))
			return (NULL);
		free(*lst);
		*lst = next;
		i++;
	}
	strarr[i] = NULL;
	return (strarr);
}