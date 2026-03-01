//init structs
//check that path for textures is valid and that textures can be loaded

#include "cub3d.h"

//store texture paths in t_config, load textures into t_texture structs in t_data
//initialize player position and direction in t_game struct
//initialize map in t_game struct
//initialize mlx and window in t_data struct
//check that all required textures are loaded and valid
//check that map is valid (proper dimensions, no invalid characters, etc.)
//check that player position is valid (within map bounds, not inside walls)
//check that floor and ceiling colors are valid (0-255 range for RGB values) 

//use getnextline to read config file line by line, parse texture paths and colors, store in t_config
//use mlx_xpm_file_to_image to load textures from paths in t_config, store in t_texture structs in t_data
    //needs to be an xpm file, so check that extension is correct before trying to load
//use mlx_init and mlx_new_window to initialize graphics, store in t_data
//use a loop to handle input, update game state, and render frames until game is closed

//open the .cub file and read it line by line using get_next_line, parse the texture paths and colors, and store them in the t_config struct. Then, use mlx_xpm_file_to_image to load the textures from the paths specified in the t_config struct and store them in the t_texture structs in the t_data struct. Next, initialize the graphics using mlx_init and mlx_new_window and store the necessary information in the t_data struct. Finally, implement a game loop that handles input, updates the game state, and renders frames until the game is closed.

// ft_get_next_line()
// mlx_xpm_file_to_image