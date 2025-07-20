#include "include/cub3D.h"

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

t_all_data	*init_all_data(void)
{
	int			fd;
	t_all_data	*all_data;

	all_data = malloc(sizeof(t_all_data));
	all_data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	all_data->image = mlx_new_image(all_data->mlx, WIDTH, HEIGHT);
	fd = open_cub_file("maps/example.cub");
	all_data->textures_and_colors = get_textures_and_colors(fd, all_data);
	get_colors(all_data);
	all_data->map = get_map(fd);
	all_data->player = malloc(sizeof(t_all_data));
	init_player(all_data->player, all_data->map);
	all_data->rays = malloc(sizeof(t_ray) * WIDTH);
	return (all_data);
}

float	handle_input(t_all_data *all_data, t_keys key)
{
	if (key == MLX_KEY_W)
		return (all_data->player->direction);
	if (key == MLX_KEY_S)
		return (all_data->player->direction + M_PI);
	if (key == MLX_KEY_A)
		return (all_data->player->direction + M_PI * -90 / 180);
	if (key == MLX_KEY_D)
		return (all_data->player->direction + M_PI * 90 / 180);
	if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
	{
		if (key == MLX_KEY_LEFT)
			all_data->player->direction -= ROTATION_SPEED;
		else if (key == MLX_KEY_RIGHT)
			all_data->player->direction += ROTATION_SPEED;
		return (-2);
	}
	return (-1);
}

void	key_hook(t_mlx_key_data d, void *all_dat)
{
	t_all_data	*all_data;
	float		move_direction;

	all_data = (t_all_data *)all_dat;
	if (all_data->player->direction < 0)
		all_data->player->direction += 2 * M_PI;
	if (all_data->player->direction >= 2 * M_PI)
		all_data->player->direction -= 2 * M_PI;
	if (d.key == MLX_KEY_ESCAPE)
		mlx_close_window(all_data->mlx);
	move_direction = handle_input(all_data, d.key);
	if (move_direction == -1
		|| all_data->map
		[(int)(all_data->player->y + sin(move_direction) * MOVEMENT_SPEED)]
		[(int)(all_data->player->x + cos(move_direction) * MOVEMENT_SPEED)]
		== '1')
		return ;
	if (move_direction != -2)
	{
		all_data->player->y += sin(move_direction) * MOVEMENT_SPEED;
		all_data->player->x += cos(move_direction) * MOVEMENT_SPEED;
	}
	cast_rays(all_data);
	ft_cub3d(all_data);
}

int	main(void)
{
	t_all_data	*all_data;

	all_data = init_all_data();
	mlx_image_to_window(all_data->mlx, all_data->image, 0, 0);
	mlx_key_hook(all_data->mlx, key_hook, (void *)all_data);
	cast_rays(all_data);
	ft_cub3d(all_data);
	mlx_loop(all_data->mlx);
}
