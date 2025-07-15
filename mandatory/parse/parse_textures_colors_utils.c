
#include "../include/cub3D.h"

int	open_cub_file(char *filename)
{
	int		fd;
	char	*found;

	found = ft_strstr(filename, ".cub");
	if (!found || found + 4 || filename == found)
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

char	**get_six_lines(int fd)
{
	int		i;
	char	**lines;

	lines = ft_calloc(7, sizeof(char *));
	i = 0;
	while (i < 6)
	{
		lines[i] = get_next_line2(fd);
		if (lines[i] == NULL)
		{
			ft_free_split(lines);
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (lines);
}

t_text_col	get_text_value(char *s)
{
	if (ft_strcmp(s, "NO") == 0)
		return (NO);
	if (ft_strcmp(s, "SO") == 0)
		return (SO);
	if (ft_strcmp(s, "WE") == 0)
		return (WE);
	if (ft_strcmp(s, "EA") == 0)
		return (EA);
	if (ft_strcmp(s, "F") == 0)
		return (F);
	if (ft_strcmp(s, "C") == 0)
		return (C);
	return (INVALID);

}

