#include "include/cub3D.h"

int main()
{
    t_mlx *mlx;
    t_mlx_image *image;

    mlx = mlx_init(800, 600, "Cub3D", true);
    image = mlx_new_image(mlx, 800, 600);
    mlx_put_pixel(image, 400, 300, 0xFFFFFF);
    mlx_image_to_window(mlx, image, 0, 0);
    mlx_loop(mlx);
}