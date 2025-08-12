/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   parse_textures_bonus.c                                                   */
/*                                                 isel-mou@student.42.fr     */
/*   By: moel-amr & isel-mou                       moel-amr@student.42.fr     */
/*                                                                            */
/*   Created: 2025/08/07 12:37:20 by moel-amr & isel-mou                      */
/*   Updated: 2025/08/07 18:23:09 by moel-amr & isel-mou                      */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

char	***validate_textures_and_colors(int fd)
{
	char	**lines;
	char	***textures_and_colors;
	int		i;

	lines = get_sixteen_lines(fd);
	textures_and_colors = ft_calloc(24, sizeof(char **));
	i = 0;
	while (i < 23)
	{
		textures_and_colors[i] = ft_split(lines[i], ' ');
		if (!textures_and_colors[i][0] || !textures_and_colors[i][1]
			|| textures_and_colors[i][2])
		{
			close(fd);
			ft_free_split(lines);
			free_splits(textures_and_colors);
			ft_putendl_fd("Error\nInvalid texture or color format", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_free_split(lines);
	return (textures_and_colors);
}

char	**sorted_files(char ***textures_and_colors)
{
	char			**sorted_files;
	t_texture_type	res;
	int				i;

	sorted_files = ft_calloc(24, sizeof(char *));
	i = 0;
	while (i < 23)
	{
		res = get_texture_type(textures_and_colors[i][0]);
		sorted_files[res] = ft_strdup(textures_and_colors[i][1]);
		i++;
	}
	free_splits(textures_and_colors);
	return (sorted_files);
}

bool	check_textures(char **textures_and_colors, t_all_data *all_data)
{
	int	i;

	i = 0;
	while (i < 21)
	{
		all_data->textures[i] = mlx_load_png(textures_and_colors[i]);
		if (!all_data->textures[i])
		{
			ft_putstr_fd("Error\nFailed to load texture: ", 2);
			ft_putendl_fd(textures_and_colors[i], 2);
			return (false);
		}
		i++;
	}
	return (true);
}

char	**get_textures_and_colors(int fd, t_all_data *all_data)
{
	char			***textures_and_colors;
	t_texture_type	count[24];
	t_texture_type	type;
	int				i;
	char			**sorted_textures;

	textures_and_colors = validate_textures_and_colors(fd);
	ft_memset(count, 0, sizeof(t_texture_type) * 24);
	i = 0;
	while (i < 23)
	{
		type = get_texture_type(textures_and_colors[i][0]);
		if (type == INVALID || count[type])
		{
			free_splits(textures_and_colors);
			ft_putendl_fd("Error\nDuplicate or invalid texture type", 2);
			return (NULL);
		}
		count[type]++;
		i++;
	}
	sorted_textures = sorted_files(textures_and_colors);
	if (check_textures(sorted_textures, all_data) == false)
		return (ft_free_split(sorted_textures), NULL);
	return (sorted_textures);
}
