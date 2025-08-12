/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   parse_utils_bonus.c                                                      */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
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
			ft_putendl_fd("Error\nMissing texture or color", 2);
			exit(EXIT_FAILURE);
		}
		if (ft_strchr(lines[i], '\n'))
			*(ft_strchr(lines[i], '\n')) = '\0';
		if (ft_strchr(lines[i], '\r'))
			*(ft_strchr(lines[i], '\r')) = '\0';
		i++;
	}
	return (lines);
}

t_texture_type	get_hand_texture_type(char *s)
{
	int					i;
	char				**hand_keys;
	t_texture_type		*hand_values;

	hand_keys = (char *[]){
		"H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8",
		"H9", "H10", "H11", "H12", "H13", "H14", "H15", "H16"
	};
	hand_values = (t_texture_type[]){
		HANDS1, HANDS2, HANDS3, HANDS4, HANDS5, HANDS6, HANDS7, HANDS8,
		HANDS9, HANDS10, HANDS11, HANDS12, HANDS13, HANDS14, HANDS15, HANDS16
	};
	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(s, hand_keys[i]) == 0)
			return (hand_values[i]);
		i++;
	}
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

void	remove_newline(char *line)
{
	char	*newline_pos;

	if (!line)
		return ;
	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
		*newline_pos = '\0';
	newline_pos = ft_strchr(line, '\r');
	if (newline_pos)
		*newline_pos = '\0';
}
