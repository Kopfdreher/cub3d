#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 100

//I am going to need a struct to store the char **map, the width and height of the map, the player position and direction, the texture paths, and the floor and ceiling colors. I will also need a struct to store the textures themselves after I load them using mlx_xpm_file_to_image. I will also need a struct to store the game state, which will include the map, player, and textures. I will also need a struct to store the input state, which will include whether the player is moving forward, backward, left, right, or rotating left or right. I will also need a struct to store the overall game state, which will include the game state and input state. I will also need a struct to store the configuration parsed from the .cub file, which will include the texture paths and floor and ceiling colors. I will also need a struct to store the parser state, which will include the file path and configuration.
//Ill probably also want a master stuct that bring them all together so I can just pass that around to all my functions instead of having to pass around a bunch of different structs. I will call this struct t_cub3d and it will include the game state, input state, and parser state. I will also include the mlx and window in this struct so I can access them from anywhere in the code. I will also include the textures in this struct so I can access them from anywhere in the code. I will also include the map in this struct so I can access it from anywhere in the code. I will also include the player in this struct so I can access it from anywhere in the code.

/*typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
    int    player_x;
    int   player_y;
    char	*texture_path[4];
    t_color	floor_color;
    t_color	ceiling_color;
}				t_map;*/

//taken from minilibx documentation, used for textures and rendering
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// structs were given to me by copilot

typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
}				t_map;

typedef struct s_player
{
    double	x;
    double	y;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
}				t_player;

typedef struct s_game
{
    t_map		map;
    t_player	player;
}				t_game;

typedef struct s_ray
{
    double	ray_dir_x;
    double	ray_dir_y;
    int		map_x;
    int		map_y;
    double	side_dist_x;
    double	side_dist_y;
    double	delta_dist_x;
    double	delta_dist_y;
    double	perp_wall_dist;
    int		step_x;
    int		step_y;
    int		hit;
    int		side;
}				t_ray;

typedef struct s_texture
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_texture;

typedef struct s_holder
{
    void		*mlx;
    void		*win;
    t_game		game;
    t_texture	textures[4];
}				t_holder;

typedef struct s_color
{
    int	rgb;
    union {
        unsigned char   r;
        unsigned char   g;
        unsigned char   b;
    };
}				t_color;

typedef struct s_config
{
    char  *no_path;
    char  *so_path;
    char  *we_path;
    char  *ea_path;
    t_color	floor_color;
    t_color	ceiling_color;
}				t_config;

typedef struct s_parser
{
    char	*file_path;
    t_config	config;
    char    *floor_red;
    char    *floor_green;
    char    *floor_blue;
    char    *ceilling_red;
    char    *ceilling_green;
    char    *ceilling_blue;
}				t_parser;   

typedef struct s_input
{
    int		forward;
    int		backward;
    int		left;
    int		right;
    int		rotate_left;
    int		rotate_right;
}				t_input;    

typedef struct s_cub3d
{
    t_data		data;
    t_parser	parser;
    t_input		input;
}				t_cub3d;


#endif
