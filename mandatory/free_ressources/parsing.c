#include "../include/cub3D.h"

void	mlx_init_error(t_all_data *all_data)
{
	free(all_data);
	ft_putendl_fd("Error", 2);
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
