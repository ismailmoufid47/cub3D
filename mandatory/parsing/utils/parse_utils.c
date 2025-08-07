/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   parse_utils.c                                                            */
/*                                                                            */
/*   By: moel-amr & isel-mou                                                  */
/*                                                                            */
/*   Created: 2025/08/07 12:33:48 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 12:33:48 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

char	**get_six_lines(int fd)
{
	int		i;
	char	**lines;

	lines = ft_calloc(7, sizeof(char *));
	i = 0;
	while (i < 6)
	{
		lines[i] = get_next_non_empty_line(fd);
		if (!lines[i])
		{
			close(fd);
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
	if (ft_strcmp(s, "F") == 0)
		return (FLOOR);
	if (ft_strcmp(s, "C") == 0)
		return (CEILING);
	return (INVALID);
}
