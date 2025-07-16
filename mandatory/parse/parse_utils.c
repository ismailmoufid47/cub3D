
#include "../include/cub3D.h"

char	*get_next_line2(int fd)
{
	char	*line;

	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (NULL);
	return (line);
}

