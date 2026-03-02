#include "cub3d.h"
void    free_cf_strarr(char **floor_colors, char **ceiling_colors, char *error_msg)
{
    if (error_msg)
        printf("%s", error_msg);
    free_strarr(&ceiling_colors);
    free_strarr(&floor_colors);
}

int color_count_check(char **floor_colors, char **ceiling_colors)
{  
    int i;
    int j;
    char *color_temp;

    i = 0;
    //I want to assign color to color_temp - check for leading white spaces, if empty, anything but numbers present, trim trailing spaces, then convert
    //then free the color and reasign color to temp and reassign color_temp to the next color and repeat
    while (floor_colors[i])
        i++;
    j = 0;
    while (ceiling_colors[j])
        j++;
    if (i != 3 || j != 3)
        return(FAILURE);
    
    return (SUCCESS);
}

void convert_colors(t_config *config, char **floor_colors, char **ceiling_colors)
{    
    int r;
    int g;
    int b;

    r = ft_atoi(floor_colors[0]);
    g = ft_atoi(floor_colors[1]);
    b = ft_atoi(floor_colors[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return(free_cf_strarr(floor_colors, ceiling_colors, "Error: Color values must be between 0 and 255\n"), FAILURE);
    config->floor_color = (r << 16) | (g << 8) | b;
    r = ft_atoi(ceiling_colors[0]);
    g = ft_atoi(ceiling_colors[1]);
    b = ft_atoi(ceiling_colors[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return(free_cf_strarr(floor_colors, ceiling_colors, "Error: Color values must be between 0 and 255\n"), FAILURE);
    config->ceiling_color = (r << 16) | (g << 8) | b;
    return (free_cf_strarr(floor_colors, ceiling_colors, NULL), SUCCESS);
}

int convert_color_str_to_int(t_config *config)
{
    char **floor_colors;
    char **ceiling_colors;

    floor_colors = ft_split(config->floor_str, ',');
    ceiling_colors = ft_split(config->ceiling_str, ',');
    if (!floor_colors || !ceiling_colors)
            return(free_cf_strarr(floor_colors, ceiling_colors, "Error: Could not allocate memory for color strings\n"), FAILURE);
    if(floor_colors && *floor_colors && ceiling_colors && *ceiling_colors)
    {
        if (color_count_check(floor_colors, ceiling_colors) == FAILURE)
            return (free_cf_strarr(floor_colors, ceiling_colors, "Error: Invalid color format\n"), FAILURE);
    }
    convert_colors(config, floor_colors, ceiling_colors);
    return (SUCCESS);
}
