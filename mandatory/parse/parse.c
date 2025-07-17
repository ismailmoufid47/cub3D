
#include "../include/cub3D.h"

int	open_cub_file(char *filename)
{
	int		fd;
	char	*found;

	found = ft_strstr(filename, ".cub");
	if (!found || *(found + 4) || found == filename)
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	print_textures_and_colors(char **textures_and_colors)
{
	int	i;

	i = 0;
	while (textures_and_colors[i])
	{
		ft_putendl_fd(textures_and_colors[i], 1);
		i++;
	}
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_putendl_fd(map[i], 1);
		i++;
	}
}

void	parse_cub_file(char	*filename)
{
	int		fd;
	char	**textures_and_colors;
	char	**map;

	fd = open_cub_file(filename);
	textures_and_colors = get_textures_and_colors(fd);
	print_textures_and_colors(textures_and_colors);
	map = get_map(fd);
	print_map(map);
}
