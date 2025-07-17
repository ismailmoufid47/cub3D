
#include "../include/cub3D.h"

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

char	***validate_text_col(int fd)
{
	char		**lines;
	char		***textures_and_colors;
	int			i;

	lines = get_six_lines(fd);
	textures_and_colors = ft_calloc(7, sizeof(char **));
	i = 0;
	while (i < 6)
	{
		textures_and_colors[i] = ft_split(lines[i], ' ');
		if (!textures_and_colors[i][0] || !textures_and_colors[i][1]
				|| textures_and_colors[i][2])
		{
			ft_free_split(lines);
			free_splits(textures_and_colors);
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_free_split(lines);
	return (textures_and_colors);
}

char	**sorted_files(char ***textures_and_colors)
{
	char		**sorted_files;
	t_text_col	res;
	int			i;

	sorted_files = ft_calloc(7, sizeof(char *));
	i = 0;
	while (i < 6)
	{
		res = get_text_value(textures_and_colors[i][0]);
		sorted_files[res] = ft_strdup(textures_and_colors[i][1]);
		i++;
	}
	free_splits(textures_and_colors);
	return (sorted_files);
}

char	**get_textures_and_colors(int fd)
{
	char		***textures_and_colors;
	t_text_col	count[6];
	t_text_col	type;
	int			i;

	textures_and_colors = validate_text_col(fd);
	ft_memset(count, 0, sizeof(t_text_col) * 6);
	i = 0;
	while (i < 6)
	{
		type = get_text_value(textures_and_colors[i][0]);
		if (type == INVALID || count[type])
		{
			free_splits(textures_and_colors);
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
		count[type]++;
		i++;
	}
	return (sorted_files(textures_and_colors));
}
