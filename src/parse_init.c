#include "cub3d.h"

int		parse_cub_file(char *argv[1], t_game *game)
{
    int i;

    game->config.file_path = argv[1];
    i = open_cub(&game->config);
    if (i != 0)
        return (1);
    if (game->config.NO_texture_path == NULL || game->config.SO_texture_path == NULL || game->config.WE_texture_path == NULL || game->config.EA_texture_path == NULL || game->config.floor_str == NULL || game->config.ceiling_str == NULL)
    {
        printf("Error: Missing texture path or color in config file\n");
        return (1);
    }
    //by this point we have successfully parsed the config file and stored all the texture paths and colors in the config struct
    //now check validity of map
    if (game->config.map == NULL)
    {
        printf("Error: Missing map in config file\n");
        return (1);
    }
    if (valid_map(&game->config, &game->player) == 1)
    {
        printf("Error: Invalid map\n");
        return (1);
    }
}

static int	check_surrounding_spaces(t_config *config, int i, int j);

//copilot broke this out so that I dont have reapeat code
static int	set_config_path(char **target, char *line, int start_idx, char *label)
{
    if (*target != NULL)
    {
        printf("Error: Duplicate %s texture path\n", label);
        return (1);
    }
    *target = ft_strdup(line + start_idx);
    if (*target == NULL)
    {
        printf("Error: Could not allocate memory for %s texture path\n", label);
        return (1);
    }
    return (0);
}

//Ignore all leading whitespaces.
//If the current row is the 0th row or the final row, only accept '1's and ' 's.
//else, The first and final character should always be a '1'.
//In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1's or ' 's.
//If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1'
//If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be '1'
//copilot was filling some of this in but I made sure to understand it and that it followed the map requirements, so I kept it. I also added some additional checks to make sure we have a map to validate and that we skip leading whitespace before checking the other conditions.

int valid_map(t_config *config, t_player *player)
{
    int i;
    int j;

    i = 0;

    if (config->map_height < 3 || config->map_width < 3)
        return (1);
    while (i < config->map_height) // first check to make sure all characters are valid and only have 1 player character
    {
        j = 0;
        while (j < config->map_width)
        {
            if (config->map[i][j] != '1' && config->map[i][j] != '0' && config->map[i][j] != ' ' && config->map[i][j] != '\0' && config->map[i][j] != 'N' && config->map[i][j] != 'S' && config->map[i][j] != 'E' && config->map[i][j] != 'W')
                return (1);
            if (config->map[i][j] == 'N' || config->map[i][j] == 'S' || config->map[i][j] == 'E' || config->map[i][j] == 'W') //Im keeping the symbol in place so we know it for later
            {
                if (player->player_char != '\0')
                    return (1);
                player->player_char = config->map[i][j];
            }
            j++;
        }
        i++;
    }
    if (player->player_char == '\0')
        return (1);
    i = 0;
    while (i < config->map_height) // then check to make sure the map is valid
    {
        j = 0;
        while (j < config->map_width)
        {
            while (config->map[i][j] == ' ')
                j++;
            if (j >= config->map_width)
                break ;
            if ((i == 0 || i == config->map_height - 1)
                && config->map[i][j] != '1' && config->map[i][j] != ' ')
                return (1);
            if ((j == 0 || j == config->map_width - 1) && config->map[i][j] != '1' && config->map[i][j] != ' ')
                return (1);
            if (config->map[i][j] == '0' || config->map[i][j] == 'N' || config->map[i][j] == 'S' || config->map[i][j] == 'E' || config->map[i][j] == 'W')
            {
                if (check_surrounding_spaces(config, i, j) == 1)
                    return (1);
            }
            j++;
        }        i++;
    }
    return (0);
}

static int	check_surrounding_spaces(t_config *config, int i, int j)
{
    if ((config->map[i][j - 1] != ' ') ) //one behind
        return (1);
    if (config->map[i][j + 1] != ' ') //one in front
        return (1);
    if (config->map[i - 1][j] != ' ') //one above
        return (1);
    if (config->map[i + 1][j] != ' ') //one below
        return (1);
    //check the corners
    if (config->map[i - 1][j - 1] != ' ') //top left corner
        return (1);
    if (config->map[i - 1][j + 1] != ' ') //top right corner
        return (1);
    if (config->map[i + 1][j - 1] != ' ') //bottom left corner
        return (1);
    if (config->map[i + 1][j + 1] != ' ') //bottom right corner
        return (1);
    return (0);
}

// int valid_map(t_game *game)
// {
//     int i;
//     int j;

//     if (game->height < 3 || game->width < 3)
//         return (1);
//     i = 0;
//     while (i < game->height)
//     {
//         j = 0;
//         while (j < game->width)
//         {
//             while (game->map[i][j] == ' ')
//                 j++;
//             if (j >= game->width)
//                 break ;
//             if ((i == 0 || i == game->height - 1)
//                 && game->map[i][j] != '1' && game->map[i][j] != ' ')
//                 return (1);
//             if ((j == 0 || j == game->width - 1) && game->map[i][j] != '1')
//                 return (1);
//             if (game->map[i][j] == ' ')
//             {
//                 if (game->map[i][j - 1] != '1' && game->map[i][j - 1] != ' ')
//                     return (1);
//                 if (game->map[i][j + 1] != '1' && game->map[i][j + 1] != ' ')
//                     return (1);
//                 if ((i > 0 && (game->map[i - 1][j] != '1' && game->map[i - 1][j] != ' '))
//                     || (i < game->height - 1
//                     && (game->map[i + 1][j] != '1' && game->map[i + 1][j] != ' ')))
//                     return (1);
//             }
//             if (i > 0 && ft_strlen(game->map[i]) > ft_strlen(game->map[i - 1])
//                 && j > (int)ft_strlen(game->map[i - 1]) && game->map[i][j] != '1')
//                 return (1);
//             if (i < game->height - 1 && ft_strlen(game->map[i]) > ft_strlen(game->map[i + 1])
//                 && j > (int)ft_strlen(game->map[i + 1]) && game->map[i][j] != '1')
//                 return (1);
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }

//step 1
//store the values so that we can use them later
//step 2

int parse_cub(char *line, t_config *config)
{
    int i;

    i = 0;
    while (line[i] == ' ')
    {
        i++;
        if (line[i] == '\0')
            return (0); //empty line, so we can ignore and move on to parsing next thing
    }
    if (line[i] == 'N' && line[i + 1] == 'O')
        return (set_config_path(&config->NO_texture_path, line, i + 2, "NO"));
    else if (line[i] == 'S' && line[i + 1] == 'O')
        return (set_config_path(&config->SO_texture_path, line, i + 2, "SO"));
    else if (line[i] == 'W' && line[i + 1] == 'E')
        return (set_config_path(&config->WE_texture_path, line, i + 2, "WE"));
    else if (line[i] == 'E' && line[i + 1] == 'A')
        return (set_config_path(&config->EA_texture_path, line, i + 2, "EA"));
    else if (line[i] == 'F')
        return (set_config_path(&config->floor_str, line, i + 1, "F"));
    else if (line[i] == 'C')
        return (set_config_path(&config->ceiling_str, line, i + 1, "C"));
    return (0);
}

static void	set_a_b_to_c(t_list **a, t_list **b, t_list **c)
{
	*a = *c;
	*b = *c;
}

char	**get_map_content(int map_fd, char *first_line, t_config *config)
{
	t_list	*head;
	t_list	*tail;
	t_list	*node;
	char	*line;

    config->map_width = 0;
	head = NULL;
    node = ft_lstnew(first_line);
    if (!node)
        return (free(first_line), NULL);
    set_a_b_to_c(&head, &tail, &node);
    config->map_width = ft_strlen(first_line);
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
        if (ft_strlen(line) > (size_t)config->map_width)
            config->map_width = ft_strlen(line);
		node = ft_lstnew(line);
		if (!node && !head)
			return (NULL);
		if (!node)
			return (ft_lstclear(&head, free), NULL);
		if (!head)
			set_a_b_to_c(&head, &tail, &node);
		else
		{
			tail->next = node;
			tail = node;
		}
	}
    config->map_height = ft_lstsize(head);
    return (ft_lst_to_strarr_width(&head, config->map_width));
}

int open_cub(t_config *config)
{
    int fd;
    char *line;
    int i;

    i = 0;
    if (!config->file_path)
    {
        printf("Error: No map file path provided\n");
        return (1);
    }
    fd = open(config->file_path, O_RDONLY);
    if (fd < 0)    
    {
        printf("Error: Could not open file\n");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        i = 0;
        while (line[i] == ' ')
        {
            i++;
            if (line[i] == '\0' /*&& map array isnt empty return - if it isnt empty store this in the map and then return for next line*/)
                break; //empty line, so we can ignore and move on to parsing next thing
            if (line[i] == '1' || line[i] == '0') //we have reached the map, so we can stop parsing the config and move on to parsing the map. We also want to make sure that we actually have a map to parse and that we dont just have a line with spaces and then end of line, because that would mean we have no map
            {
                config->map = get_map_content(fd, line, &config);
                if (!config->map)
                {
                    close(fd);
                    return (1);
                }
                close(fd);
                return (0);
            }
            else if (parse_cub(line, config) == 1)
            {
                //do I also need to free the config struct 
                free(line);
                close(fd);
                return (1);
            }
        }
        free(line);
    }
    close(fd);
    return (1);
}
