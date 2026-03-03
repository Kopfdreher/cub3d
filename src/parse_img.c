#include "cub3d.h"
int parse_img(t_game *game)
{
    //if i am passing _gam - it has the relatie paths from t_config
    //it has *mls and *win from t_gfx
    void	*mlx;
	void	*img;
	char	*relative_path = game->config.no_texture_path; //example for now, will need to loop through all 4 textures
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}