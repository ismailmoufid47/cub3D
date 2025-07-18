
#include "../include/cub3D.h"

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
	all_data->textures[NO] = mlx_load_png(textures_and_colors[NO]);
	if (!all_data->textures[NO])
		return (false);
	all_data->textures[SO] = mlx_load_png(textures_and_colors[SO]);
	if (!all_data->textures[SO])
		return (false);
	all_data->textures[WE] = mlx_load_png(textures_and_colors[WE]);
	if (!all_data->textures[WE])
		return (false);
	all_data->textures[EA] = mlx_load_png(textures_and_colors[EA]);
	if (!all_data->textures[EA])
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
			textures_and_colors_error(textures_and_colors);
		count[type]++;
		i++;
	}
	sorted_textures = sorted_files(textures_and_colors);
	if (check_textures(sorted_textures, all_data) == false)
		pre_map_error(sorted_textures);
	return (sorted_textures);
}

void	get_colors(t_all_data *all_data)
{
	char	**ceil;
	char	**floor;

	ceil = ft_split(all_data->textures_and_colors[C], ',');
	floor = ft_split(all_data->textures_and_colors[F], ',');
	if ((!ceil || (!ceil[0] || ft_atoi(ceil[0]) > 255 || ft_atoi(ceil[0]) < 0)
			|| (!ceil[1] || ft_atoi(ceil[1]) > 255 || ft_atoi(ceil[1]) < 0)
			|| (!ceil[2] || ft_atoi(ceil[2]) > 255 || ft_atoi(ceil[2]) < 0)
			|| ceil[3]) || ((!floor[0] || ft_atoi(floor[0]) > 255
				|| ft_atoi(floor[0]) < 0) || (!floor[1]
				|| ft_atoi(floor[1]) > 255 || ft_atoi(floor[1]) < 0)
			|| (!floor[2] || ft_atoi(floor[2]) > 255 || ft_atoi(floor[2]) < 0)
			|| floor[3]))
	{
		ft_free_split(ceil);
		ft_free_split(floor);
		pre_map_error(all_data->textures_and_colors);
	}
	all_data->C_color = (255) + (ft_atoi(ceil[0]) << 24) + (ft_atoi(ceil[1]) << 16) + (ft_atoi(ceil[2]) << 8);
	all_data->F_color = (255) + (ft_atoi(floor[0]) << 24) + (ft_atoi(floor[1]) << 16) + (ft_atoi(floor[2]) << 8);
	ft_free_split(ceil);
	ft_free_split(floor);
}
