#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	my_close(t_vars *v)
// {
// 	if (v->img.img)
// 		mlx_destroy_image(v->ctx.link, v->img.img);
// 	if (v->ctx.win)
// 		mlx_destroy_window(v->ctx.link, v->ctx.win);
// 	if (v->ctx.link)
// 		mlx_destroy_display(v->ctx.link);
// 	free(v->ctx.link);
// }


// step 1
// open and parse .cub
// step 2
// initialize game state and graphics
// step 3
// game loop: handle input, update game state, render frame
// step 4
// close graphics and free resources

int main(void)
{
    //dont forget to always initialize all structs to null or 0 so we dont have any garbage values that could cause issues later on
    //t_config config;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

    int i;
    i = open_cub();
    if (i == 0)
        return (0);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0xB5DBF4);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

    /*if no map 
        return error
    send map to parser
    if parser error
        return error
    initialize game state
    initialize graphics
    while game is running
        handle input
        update game state
        render frame
    close graphics*/
    //config_valid(config);
    return (0);
}