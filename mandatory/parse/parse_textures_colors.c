
#include "../include/cub3D.h"

char	***validate_text_col(char **lines)
{
	char	***textures_and_colors;
	int		i;

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
	}
	ft_free_split(lines);
	return (textures_and_colors);
}

char	**get_sorted_files(char ***textures_and_colors)
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
	}
	free_splits(textures_and_colors);
	return (sorted_files);
}

char	**get_textures_and_colors(char ***textures_and_colors)
{
	t_text_col	text_cols[6];
	t_text_col	res;
	int			i;

	ft_memset(text_cols, 0, sizeof(t_text_col) * 6);
	i = 0;
	while (i < 6)
	{
		res = get_text_value(textures_and_colors[i][0]);
		if (res == INVALID || text_cols[res] == 1)
		{
			free_splits(textures_and_colors);
			ft_putendl_fd("Error", 2);
			exit(EXIT_FAILURE);
		}
		text_cols[res]++;
	}
	return (get_sorted_files(textures_and_colors));
}

