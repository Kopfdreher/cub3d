#include "cub3d.h"

char **insert_content(t_list **lst, char **strarr, int width, int i, t_list *next)
{
	char *content;
	int j;

	content = (char *)(*lst)->content;
	strarr[i] = malloc(sizeof(char) * (width + 1));
		if (!strarr[i])
		{
			free(*lst);
			*lst = next;
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
		free (content); //should I actualy be freeing this here
		return (strarr);
}

char	**ft_lst_to_strarr_width(t_list **lst, int width) //have changed this to pass the width
{
	//copilot filled this in but I fully understand it
	int		lst_size;
	t_list	*next;
	int		i;
	char	**strarr;

	if (width < 0)
		width = 0;
	lst_size = ft_lstsize(*lst);
	strarr = malloc(sizeof(char *) * (lst_size + 1));
	if (!strarr)
		return (ft_lstclear(lst, free), NULL);
	i = 0;
	while (*lst)
	{
		next = (*lst)->next;
		if (!insert_content(lst, strarr, width, i, next))
			return (NULL);
		free(*lst);
		*lst = next;
		i++;
	}
	strarr[i] = NULL;
	return (strarr);
}