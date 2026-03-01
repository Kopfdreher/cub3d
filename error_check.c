//check if all required textures are loaded and valid
//check if map is valid (proper dimensions, no invalid characters, etc.)
//check if player position is valid (within map bounds, not inside walls)
//check if floor and ceiling colors are valid (0-255 range for RGB values)
#include "cub3d.h"

//but still need to check if something is actually there to store in t_texture
// int valid_textures(t_data *data)
// {
//     int i;
//     i = 0;
//     while (i < 4)
//     {
//         if (data->textures[i].img == NULL)
//             return (0);
//         i++;
//     }
//     return (1);
// }

// I need to make sure I store the first row of the map as the first row that has 1s when I am adding the map to the t_map struct amd that the map that has the first 1 is where we start from and the one with last 1 is where we end - s0o standardize
//but also adding here a check to see if player is out of bounds
//wait is it safe to just dd to strcut based on firt time encontering 1s, then if we just never encounter player we can return error - this means that player either wasnt present or was out of bounds
int valid_player(t_map map)
{
    //check if player position is valid (within map bounds, not inside walls)
    int i;
    int j;
    i = 0;
    j = 0;
    while (i < map.height)
    {   while (j < map.width)
        {           
        //locate player
        if (map.map[i][j] == 'N' || map.map[i][j] == 'S' || map.map[i][j] == 'E' || map.map[i][j] == 'W')
        {
            if (map.map[i][j - 1] != '1' && map.map[i][j - 1] != '0') //one character before current space should be '1' or '0'
                return (0);
            if (map.map[i][j + 1] != '1' && map.map[i][j + 1] != '0') //one character after current space should be '1' or '0'
                return (0);
            if ((i > 0 && (map.map[i - 1][j] != '1' && map.map[i - 1][j] != '0')) ||
            (i < map.height - 1 && (map.map[i + 1][j] != '1' && map.map[i + 1][j] != '0')))
                return (0);//check if spot above and below is '1' or '0' and we are not on the first or last row      
            return (1);  
        }
        j = 0;
        i++;
        }
    }
    return (0); // we never found a player, so either there was no player or the player was out of bounds
}
//copilot filled check ceiling and floor color checks, but I understand them
int check_ceiling(t_config *config)
{
    //check if ceiling color is valid (0-255 range for RGB values)
    if (config->ceiling_color.r < 0 || config->ceiling_color.r > 255 ||
        config->ceiling_color.g < 0 || config->ceiling_color.g > 255 ||
        config->ceiling_color.b < 0 || config->ceiling_color.b > 255)
    {
        return (0);
    }
    return (1);
}
int check_floor(t_config *config)
{
    //check if floor color is valid (0-255 range for RGB values)
    if (config->floor_color.r < 0 || config->floor_color.r > 255 ||
        config->floor_color.g < 0 || config->floor_color.g > 255 ||
        config->floor_color.b < 0 || config->floor_color.b > 255)
    {
        return (0);
    }
    return (1);
}

// int config_valid(t_config *config)
// {
//     if (!check_ceiling(config) || !check_floor(config) || !valid_textures(config) || !valid_map(config) || !valid_player(config))
//         return (0);
//     return (1);
// }
