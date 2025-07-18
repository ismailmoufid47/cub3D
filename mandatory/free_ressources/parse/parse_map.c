
#include "../../include/cub3D.h"

void	textures_and_colors_error(char ***textures_and_colors)
{
	free_splits(textures_and_colors);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

void	pre_map_error(char **map)
{
	ft_free_split(map);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}
