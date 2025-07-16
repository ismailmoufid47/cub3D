
#include "../../include/cub3D.h"

void	pre_map_error(char **map)
{
	ft_free_split(map);
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}
