/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   parse_utils_bonus.c                                                      */
/*                                                                            */
/*   By: moel-amr & isel-mou                                                  */
/*                                                                            */
/*   Created: 2025/08/07 12:36:56 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 18:23:38 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

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

char	**get_sixteen_lines(int fd)
{
	int		i;
	char	**lines;

	lines = ft_calloc(24, sizeof(char *));
	i = 0;
	while (i < 23)
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

t_texture_type	get_hand_texture_type(char *s)
{
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
	if (ft_strcmp(s, "H6") == 0)
		return (HANDS6);
	if (ft_strcmp(s, "H7") == 0)
		return (HANDS7);
	if (ft_strcmp(s, "H8") == 0)
		return (HANDS8);
	if (ft_strcmp(s, "H9") == 0)
		return (HANDS9);
	if (ft_strcmp(s, "H10") == 0)
		return (HANDS10);
	if (ft_strcmp(s, "H11") == 0)
		return (HANDS11);
	if (ft_strcmp(s, "H12") == 0)
		return (HANDS12);
	if (ft_strcmp(s, "H13") == 0)
		return (HANDS13);
	if (ft_strcmp(s, "H14") == 0)
		return (HANDS14);
	if (ft_strcmp(s, "H15") == 0)
		return (HANDS15);
	if (ft_strcmp(s, "H16") == 0)
		return (HANDS16);
	return (INVALID);
}

t_texture_type	get_texture_type(char *s)
{
	t_texture_type	hand_type;

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
	if (ft_strcmp(s, "F") == 0)
		return (FLOOR);
	if (ft_strcmp(s, "C") == 0)
		return (CEILING);
	hand_type = get_hand_texture_type(s);
	if (hand_type != INVALID)
		return (hand_type);
	return (INVALID);
}
