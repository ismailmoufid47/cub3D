
#include "../include/cub3D.h"

bool ft_compare(char c)
{
	if (c == '0' || c == '1' || c == 'N')
		return true;
	if (c == 'S' || c == 'W' || c == 'E')
		return true;
	return false;
}

void	validate_map(char	**map_lines)
{
	char c;
	int hash_table[255]; 

	ft_memset(hash_table,0,sizeof(int) * 255);
	while (*map_lines)
	{
		while (**map_lines)
		{
			c = **map_lines;
			if (ft_compare(c) == false)
				printf("error"); //change later
			hash_table[c]++;
			if (hash_table[c] > 1)
				printf("error"); //chane later
				*map_lines++;
		}
		map_lines++;
	}
}

char	**get_map(int fd)
{
	char	**map_lines;
	int		size;

	map_lines = calloc(1, sizeof(char *));
	map_lines[0] = get_next_line2(fd);
	size = 1;
	while (map_lines[size])
	{
		map_lines = ft_realloc(map_lines, size * sizeof(char *),
				(size + 1) * sizeof(char *));
		*(ft_strchr(map_lines[size], '\n')) = '\0';
		size++;
	}
	
	return (map_lines);
}

void	parse_cub_file(char	*filename)
{
	int		fd;
	char	**textures_and_colors;

	fd = open_cub_file(filename);
	textures_and_colors = 
		get_textures_and_colors(validate_text_col(get_six_lines(fd)));
	
}
