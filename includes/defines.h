/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:27:15 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/03 15:27:41 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

// Our Libft
# include "../libft/libft.h"

// MACROS ----------------------------------------------------------------------

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define FALSE 0
# define TRUE 1

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEXTURE_SIZE 64

# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363
# define K_ESC 65307

// ENUMS -----------------------------------------------------------------------

typedef enum e_direction {
	NORTH, // 0
	SOUTH, // 1
	WEST, // 2
	EAST // 3
}	t_direction;

// STRUCTS ---------------------------------------------------------------------

typedef struct s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
} t_keys;

typedef struct s_config {
	char		*file_path;
	char		**map;
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	char		*floor_str;
	char		*ceiling_str;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
}	t_config;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	player_char;
} t_player;

typedef struct s_img {
	void	*img;// this is what mlx_xpm_file_to_image returns //dont forget to mlx_destroy_image if get data doesnt work
	char	*addr; //this is what mlx_get_data_addr returns
	int		bpp; //send these nxt 3 to mlx_get_data_addr and it will fill them in for you
	int		line_len;
	int		endian;
} t_img;

typedef struct s_graphics {
	void	*mlx;
	void	*win;
	t_img	buff;
	t_img	textures[4];  // NORTH, SOUTH, WEST, EAST
} t_graphics;

typedef struct s_game {
	t_config	config;
	t_player	player;
	t_graphics	gfx;
	t_keys		keys;
} t_game;

#endif
