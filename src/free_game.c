#include "cub3d.h"
int free_parse(t_config *config)
{
    if(config->NO_texture_path)
        free(config->NO_texture_path);
    if(config->SO_texture_path)
        free(config->SO_texture_path);
    if(config->WE_texture_path)
        free(config->WE_texture_path);
    if(config->EA_texture_path)
        free(config->EA_texture_path);
    if(config->floor_str)
        free(config->floor_str);
    if(config->ceiling_str)
        free(config->ceiling_str);
    free_strarr(&config->map);
    config->NO_texture_path = NULL;
    config->SO_texture_path = NULL;
    config->WE_texture_path = NULL;
    config->EA_texture_path = NULL;
    config->floor_str = NULL;
    config->ceiling_str = NULL;
    config->map = NULL;
    return (0);
}
