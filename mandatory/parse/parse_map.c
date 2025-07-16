
#include "../include/cub3D.h"


bool	is_valid_adjecent(char **map, int y, int x)
{
	if (x < 0)
		return (false);
	else if (y < 0)
		return (false);
	else if (x == ft_strlen(map[y]))
		return (false);
	else if (map[y] == NULL)
		return (false);
	if (map[y][x] == ' ')
		return (false);
	return (true);
}

void	filling_the_map(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSWE0", map[y][x]))
			{
				if (!is_valid_player_adjecent(map, y - 1, x)
					|| !is_valid_player_adjecent(map, y + 1, x)
					|| !is_valid_player_adjecent(map, y, x - 1)
					|| is_valid_player_adjecent(map, y, x + 1))
					pre_map_error(map);
			}
			x++;
		}
		y++;
	}
}

void	validate_map(char	**map)
{
	int		count[255];
	int		y;
	int		x;

	ft_memset(count, 0, sizeof(int) * 255);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			count[(int)map[y][x]]++;
			if ((count['N'] + count['S'] + count['W'] + count['E'] > 1)
				|| !ft_strchr("01NSWE ", map[y][x]))
				pre_map_error(map);
			x++;
		}
		y++;
	}
	if (count['N'] + count['S'] + count['W'] + count['E'] != 1)
		pre_map_error(map);
}

char	**get_map(int fd)
{
	char	**map;
	int		size;

	size = 2;
	map = ft_calloc(size, sizeof(char *));
	map[0] = get_next_line2(fd);
	if (!map[0])
		pre_map_error(map);
	if (map[0] && ft_strchr(map[0], '\n'))
		*(ft_strchr(map[0], '\n')) = '\0';
	while (map[size - 2])
	{
		map = ft_realloc(map, size * sizeof(char *),
				(size + 1) * sizeof(char *));
		map[size - 1] = get_next_line(fd);
		map[size] = NULL;
		if ((map[size - 1]
				&& ft_strchr(map[size - 1], '\n') == map[size - 1]))
			pre_map_error(map);
		if (map[size - 1] && ft_strchr(map[size - 1], '\n'))
			*(ft_strchr(map[size - 1], '\n')) = '\0';
		size++;
	}
	validate_map(map);
	return (map);
}
