#include "../include/cub3D_bonus.h"

void	mlx_init_error(void)
{
	ft_putendl_fd("Error: mlx_init failed", 2);
	exit(EXIT_FAILURE);
}

void	pre_textures_and_colors_error(char ***textures_and_colors)
{
	free_splits(textures_and_colors);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

void	post_textures_and_colors_error(char **textures_and_colors)
{
	ft_free_split(textures_and_colors);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}
