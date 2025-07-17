#include "include/cub3D.h"

int	main(void)
{
	t_mlx	*mlx;

	mlx = mlx_init(800, 600, "Cub3D", true);

	mlx_put_pixel(mlx, 400, 300, 0xFFFFFF);
	mlx_loop(mlx);
	mlx_destroy(mlx);

	printf("Welcome to the Cub3D game!\n");
}
