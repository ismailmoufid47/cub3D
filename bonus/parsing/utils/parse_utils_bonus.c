#include "../../include/cub3D_bonus.h"

char	*get_next_non_empty_line(int fd)
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
	return (line);
}

char	**get_twelve_lines(int fd)
{
	int		i;
	char	**lines;

	lines = ft_calloc(13, sizeof(char *));
	i = 0;
	while (i < 12)
	{
		lines[i] = get_next_non_empty_line(fd);
		if (!lines[i])
		{
			ft_free_split(lines);
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
		if (ft_strchr(lines[i], '\n'))
			*(ft_strchr(lines[i], '\n')) = '\0';
		i++;
	}
	return (lines);
}

t_texture_type	get_texture_type(char *s)
{
	if (ft_strcmp(s, "NO") == 0)
		return (NORTH);
	if (ft_strcmp(s, "SO") == 0)
		return (SOUTH);
	if (ft_strcmp(s, "WE") == 0)
		return (WEST);
	if (ft_strcmp(s, "EA") == 0)
		return (EAST);
	if (ft_strcmp(s, "DO") == 0)
		return (DOOR);
	if (ft_strcmp(s, "H1") == 0)
		return (HANDS1);
	if (ft_strcmp(s, "H2") == 0)
		return (HANDS2);
	if (ft_strcmp(s, "H3") == 0)
		return (HANDS3);
	if (ft_strcmp(s, "H4") == 0)
		return (HANDS4);
	if (ft_strcmp(s, "H5") == 0)
		return (HANDS5);
	if (ft_strcmp(s, "F") == 0)
		return (FLOOR);
	if (ft_strcmp(s, "C") == 0)
		return (CEILING);
	return (INVALID);
}
