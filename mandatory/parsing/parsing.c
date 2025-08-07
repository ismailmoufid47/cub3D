/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-amr <moel-amr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:34:36 by moel-amr          #+#    #+#             */
/*   Updated: 2025/08/07 12:34:36 by moel-amr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	open_cub_file(char *filename)
{
	int		fd;
	char	*found;

	found = ft_strstr(filename, ".cub");
	if (!found || *(found + 4) || found == filename
		|| ft_strrchr(filename, '/') + 1 == found)
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	init_player(t_player	*player, char **map)
{
	int			y;
	int			x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] && !ft_strchr("NSWE", map[y][x]))
			x++;
		if (ft_strchr("NSWE", map[y][x]))
			break ;
		y++;
	}
	player->y = y + 0.5;
	player->x = x + 0.5;
	if (map[y][x] == 'N')
		player->direction = 3 * M_PI / 2;
	if (map[y][x] == 'S')
		player->direction = M_PI / 2;
	if (map[y][x] == 'W')
		player->direction = M_PI;
	if (map[y][x] == 'E')
		player->direction = 0;
}

bool	set_colors(t_all_data *all_data)
{
	char	**ceil;
	char	**flor;

	ceil = ft_split(all_data->textures_and_colors[CEILING], ',');
	flor = ft_split(all_data->textures_and_colors[FLOOR], ',');
	if ((!ceil || (!ceil[0] || ft_atoi(ceil[0]) > 255 || ft_atoi(ceil[0]) < 0)
			|| (!ceil[1] || ft_atoi(ceil[1]) > 255 || ft_atoi(ceil[1]) < 0)
			|| (!ceil[2] || ft_atoi(ceil[2]) > 255 || ft_atoi(ceil[2]) < 0)
			|| ceil[3])
		|| ((!flor[0] || ft_atoi(flor[0]) > 255 || ft_atoi(flor[0]) < 0)
			|| (!flor[1] || ft_atoi(flor[1]) > 255 || ft_atoi(flor[1]) < 0)
			|| (!flor[2] || ft_atoi(flor[2]) > 255 || ft_atoi(flor[2]) < 0)
			|| flor[3]))
	{
		ft_free_split(ceil);
		ft_free_split(flor);
		return (false);
	}
	all_data->ceiling_color = (255 << 24)
		+ (ft_atoi(ceil[2]) << 16) + (ft_atoi(ceil[1]) << 8) + ft_atoi(ceil[0]);
	all_data->floor_color = (255 << 24)
		+ (ft_atoi(flor[2]) << 16) + (ft_atoi(flor[1]) << 8) + ft_atoi(flor[0]);
	ft_free_split(ceil);
	ft_free_split(flor);
	return (true);
}

t_all_data	*init_all_data(char *filename)
{
	int			fd;
	t_all_data	*all_data;
	t_mlx_image	*image;

	all_data = malloc(sizeof(t_all_data));
	all_data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!all_data->mlx)
		mlx_init_error(all_data);
	fd = open_cub_file(filename);
	all_data->textures_and_colors = get_textures_and_colors(fd, all_data);
	if (!all_data->textures_and_colors || !set_colors(all_data))
		post_textures_and_colors_error(all_data->textures_and_colors, fd);
	all_data->map = get_map(fd);
	if (!all_data->map)
		post_textures_and_colors_error(all_data->textures_and_colors, fd);
	close(fd);
	image = mlx_new_image(all_data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(all_data->mlx, image, 0, 0);
	all_data->window_pixels
		= (uint32_t *)image->pixels;
	all_data->player = malloc(sizeof(t_player));
	init_player(all_data->player, all_data->map);
	all_data->rays = malloc(sizeof(t_ray) * WIDTH);
	init_input_state(all_data);
	return (all_data);
}
