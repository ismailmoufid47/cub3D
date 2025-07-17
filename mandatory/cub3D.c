#include "include/cub3D.h"

t_player	*init_player(char **map)
{
	t_player	*player;
	int			y;
	int			x;

	player = malloc(sizeof(t_player));
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
		player->direction = 3 * PI / 2;
	if (map[y][x] == 'S')
		player->direction = PI / 2;
	if (map[y][x] == 'W')
		player->direction = PI;
	if (map[y][x] == 'E')
		player->direction = 0;
	return (player);
}

t_all_data	*init_all_data(void)
{
	int			fd;
	t_all_data	*all_data;

	all_data = malloc(sizeof(t_all_data));
	all_data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	all_data->image = mlx_new_image(all_data->mlx, WIDTH, HEIGHT);
	fd = open_cub_file("maps/example.cub");
	all_data->textures_and_colors = get_textures_and_colors(fd);
	all_data->map = get_map(fd);
	all_data->player = init_player(all_data->map);
	all_data->rays = malloc(sizeof(t_ray));
	return (all_data);
}

int	main(void)
{
	t_all_data	*all_data;

	all_data = init_all_data();
	mlx_image_to_window(all_data->mlx, all_data->image, 0, 0);
	ray_casting(all_data,  all_data->player->direction);
	mlx_loop(all_data->mlx);
}