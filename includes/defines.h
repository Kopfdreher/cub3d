/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:27:15 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/03/07 11:55:16 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

// Our Libft
# include "../libft/libft.h"

// MACROS ----------------------------------------------------------------------

// Returns
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define FALSE 0
# define TRUE 1

// Imgs
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define TEXTURE_SIZE 64

// Keys
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363
# define K_ESC 65307

// Movement
# define MOVEMENT_SPEED 0.06
# define ROTATE_SPEED 0.06

// POS
# define Y 0
# define X 1

// ENUMS -----------------------------------------------------------------------

typedef enum e_dir {
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_dir;

// STRUCTS ---------------------------------------------------------------------

typedef struct s_ray {
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	t_dir	wall_dir;
}	t_ray;

typedef struct s_keys {
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_color {
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
}	t_color;

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
	//int			floor_color;
	//int			ceiling_color;
	union
	{
		int		color;
		t_color	rgb;
	} u_floor_color;
	union
	{
		int		color;
		t_color	rgb;
	} u_ceiling_color;
}	t_config;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	player_char;
}	t_player;

typedef struct s_img {
	void	*img;// this is what mlx_xpm_file_to_image returns //dont forget to mlx_destroy_image if get data doesnt work
	char	*addr; //this is what mlx_get_data_addr returns
	int		bpp; //send these nxt 3 to mlx_get_data_addr and it will fill them in for you
	int		line_len;
	int		endian;
	int		width; //store width and height for convenience
	int		height;
}	t_img;

// t_img	textures[4];  NORTH, SOUTH, WEST, EAST
typedef struct s_graphics {
	void		*mlx;
	void		*win;
	t_img		buff;
	t_img		textures[4];
	long long	last_frame_time;
}	t_graphics;

typedef struct s_game {
	t_config	config;
	t_player	player;
	t_graphics	gfx;
	t_keys		keys;
}	t_game;

#endif
