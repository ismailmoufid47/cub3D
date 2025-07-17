
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

