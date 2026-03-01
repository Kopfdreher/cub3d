/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:27:15 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/01 16:31:35 by sgavrilo         ###   ########.fr       */
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
	NORTH,
	SOUTH,
	WEST,
	EAST
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

typedef struct s_data {
	char	**map;
	int		map_width;
	int		map_height;
	int		floor_color;
	int		ceiling_color;
	char	*tex_paths[4]; // NORTH, SOUTH, WEST, EAST
} t_data;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
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
	t_data		data;
	t_player	player;
	t_graphics	gfx;
	t_keys		keys;
} t_game;

#endif
