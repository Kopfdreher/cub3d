/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_map_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:49:24 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 13:24:53 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*sets head and tail to the same node for the first node in the list*/
static void	set_a_b_to_c(t_list **a, t_list **b, t_list **c)
{
	*a = *c;
	*b = *c;
}

/*called from get_map_content
sets a new node with the line content and adds it to the end of the list
does a malloc check and if it fails clears the list and frees the line content 
	if we had already added a node to the list,
	otherwise just returns failure since we 
	didnt have anything to clear
sends to set_a_b_to_c to set head and tail if this is the first node, 
	otherwise just adds to the end and updates tail
*/
static int	add_nodes_to_list(char *line, t_list **head, t_list **tail)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node && !*head)
		return (FAILURE);
	if (!node)
		return (ft_lstclear(head, free), FAILURE);
	if (!*head)
		set_a_b_to_c(head, tail, &node);
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
	return (SUCCESS);
}

/*
 * helper function to initialize the map list also handles first line
*/
static int	init_map_list(t_list **head, t_list **tail, char *first_line, 
		t_config *config)
{
	t_list	*node;

	config->map_width = 0;
	*head = NULL;
	node = ft_lstnew(first_line);
	if (!node)
		return (free(first_line), FAILURE);
	set_a_b_to_c(head, tail, &node);
	config->map_width = ft_strlen(first_line);
	return (SUCCESS);
}

/*helper function to get the map content
sends to a helper function that initiates the map list and handles the first line
then reading line by line 
updates map width if the lin is the longest we have encountered
then sends to a helper to add nodes
then sets height of map to the number of lines read (nodes)
upon success returns the map content as a string array 
	having sent it to ft_lst_to_strarr_width*/
static char	**get_map_content(int map_fd, char *first_line, t_config *config)
{
	t_list	*head;
	t_list	*tail;
	char	*line;

	if (init_map_list(&head, &tail, first_line, config) == FAILURE)
		return (NULL);
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		if (ft_strlen(line) > (size_t)config->map_width)
			config->map_width = ft_strlen(line);
		if (add_nodes_to_list(line, &head, &tail) == FAILURE)
			return (NULL);
	}
	config->map_height = ft_lstsize(head);
	return (ft_lst_to_strarr_width(&head, config->map_width));
}

/*receives the file descriptor and the first line of the map content
then sends to a helper function which reads the rest of the map content
closes fd on failure*/
int	assign_map_content(t_config *config, int fd, char *line)
{
	config->map = get_map_content(fd, line, config);
	if (!config->map)
		return (close(fd), FAILURE);
	return (close(fd), SUCCESS);
}
