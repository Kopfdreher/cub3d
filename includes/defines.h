/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:27:15 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/01 17:40:09 by sgavrilo         ###   ########.fr       */
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
	char		*NO_texture_path;
	char		*SO_texture_path;
	char		*WE_texture_path;
	char		*EA_texture_path;
	char		*floor_str;
	char		*ceiling_str;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
} t_config;

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
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_graphics {
	void	*mlx;
	void	*win;
	t_img	buffer;
	t_img	textures[4];  // NORTH, SOUTH, WEST, EAST
} t_graphics;

typedef struct s_game {
	t_config	config;
	t_player	player;
	t_graphics	gfx;
	t_keys		keys;
} t_game;

#endif
