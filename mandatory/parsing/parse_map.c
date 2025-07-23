#include "../include/cub3D.h"

bool	is_valid_adjecent(char **map, int y, int x)
{
	if (x < 0)
		return (false);
	else if (y < 0)
		return (false);
	else if (map[y] == NULL)
		return (false);
	if (ft_strlen(map[y]) <= (unsigned)x || map[y][x] == ' ')
		return (false);
	return (true);
}

bool	is_valid(char **map, int y, int x)
{
	if (!ft_strchr("0NSWE 1", map[y][x]))
		return (false);
	if (ft_strchr("0NSWE", map[y][x]))
	{
		if (!is_valid_adjecent(map, y - 1, x)
			|| !is_valid_adjecent(map, y + 1, x)
			|| !is_valid_adjecent(map, y, x - 1)
			|| !is_valid_adjecent(map, y, x + 1))
			return (false);
	}
	return (true);
}

char	**validate_map(char **map)
{
	static int		count[255];
	static int		y;
	int				x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			count[(int)map[y][x]]++;
			if (!is_valid(map, y, x))
			{
				ft_free_split(map);
				return (NULL);
			}
			x++;
		}
		y++;
	}
	if (count['N'] + count['S'] + count['W'] + count['E'] != 1)
	{
		ft_free_split(map);
		return (NULL);
	}
	return (map);
}

char	**get_map(int fd)
{
	char	**map;
	int		size;

	size = 2;
	map = ft_calloc(size, sizeof(char *));
	map[0] = get_next_non_empty_line(fd);
	if (!map[0])
	{
		ft_free_split(map);
		return (NULL);
	}
	if (ft_strchr(map[0], '\n'))
		*ft_strchr(map[0], '\n') = '\0';
	while (map[size - 2])
	{
		map = ft_recalloc(map, size * sizeof(char *),
				(size + 1) * sizeof(char *));
		map[size - 1] = get_next_line(fd);
		if (map[size - 1])
			if (ft_strchr(map[size - 1], '\n'))
				*ft_strchr(map[size - 1], '\n') = '\0';
		size++;
	}
	return (validate_map(map));
}
