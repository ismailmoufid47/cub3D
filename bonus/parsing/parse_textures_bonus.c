#include "../include/cub3D_bonus.h"

char	***validate_textures_and_colors(int fd)
{
	char	**lines;
	char	***textures_and_colors;
	int		i;

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

bool	check_textures(char **textures_and_colors, t_all_data *all_data)
{
	all_data->textures[NORTH] = mlx_load_png(textures_and_colors[NORTH]);
	if (!all_data->textures[NORTH])
		return (false);
	all_data->textures[SOUTH] = mlx_load_png(textures_and_colors[SOUTH]);
	if (!all_data->textures[SOUTH])
		return (false);
	all_data->textures[WEST] = mlx_load_png(textures_and_colors[WEST]);
	if (!all_data->textures[WEST])
		return (false);
	all_data->textures[EAST] = mlx_load_png(textures_and_colors[EAST]);
	if (!all_data->textures[EAST])
		return (false);
	return (true);
}

char	**get_textures_and_colors(int fd, t_all_data *all_data)
{
	char		***textures_and_colors;
	t_text_col	count[6];
	t_text_col	type;
	int			i;
	char		**sorted_textures;

	textures_and_colors = validate_textures_and_colors(fd);
	ft_memset(count, 0, sizeof(t_text_col) * 6);
	i = 0;
	while (i < 6)
	{
		type = get_text_value(textures_and_colors[i][0]);
		if (type == INVALID || count[type])
			return (NULL);
		count[type]++;
		i++;
	}
	sorted_textures = sorted_files(textures_and_colors);
	if (check_textures(sorted_textures, all_data) == false)
	{
		ft_free_split(sorted_textures);
		return (NULL);
	}
	return (sorted_textures);
}
