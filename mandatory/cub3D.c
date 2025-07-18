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
	all_data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	all_data->image = mlx_new_image(all_data->mlx, WIDTH, HEIGHT);
	fd = open_cub_file("maps/example.cub");
	all_data->textures_and_colors = get_textures_and_colors(fd, all_data);
	get_colors(all_data);
	all_data->map = get_map(fd);
	all_data->player = init_player(all_data->map);
	all_data->rays = malloc(sizeof(t_ray) * N_RAYS);
	return (all_data);
}
bool	check_valid_movements(float new_y, float new_x, t_all_data *all_data)
{
	int	height;


	height = 0;
	while (all_data->map[height])
		height++;
	if (new_y <= 0)
		return (false);
	if (new_x <= 0)
		return (false);
	if (new_y >= (float)height)
		return (false);
	printf("ha fin khwrtha y=%f x=%f limit = %f\n",new_y,new_x,(float)ft_strlen(all_data->map[(int)new_y]) - 1);
	if (new_x >= ft_strlen(all_data->map[(int)new_y]) - 1)
	{
		printf("trueee\n");
		return (false);
	}
	printf("dazelihaaa\n");
	if(all_data->map[(int)new_y][(int)new_x] == '1')
		return false;
	all_data->player->x = new_x;
	all_data->player->y = new_y;
	return (true);
}

void	key_hook(t_mlx_key_data key, void *all_dat)
{
	t_all_data	*all_data;
	float		new_y;
	float		new_x;

	all_data = (t_all_data *)all_dat;
	new_x = all_data->player->x;
	new_y = all_data->player->y;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(all_data->mlx);
	if (key.key == MLX_KEY_W)
	{
		new_y += sin(all_data->player->direction) * STEP;
		new_x += cos(all_data->player->direction) * STEP;
	}
	if (key.key == MLX_KEY_S)
	{
		new_y += sin(all_data->player->direction) * -STEP;
		new_x += cos(all_data->player->direction) * -STEP;
	}
	if (key.key == MLX_KEY_A)
	{
		new_y += sin(all_data->player->direction - PI * 90 / 180) * STEP;
		new_x += cos(all_data->player->direction - PI * 90 / 180) * STEP;
	}
	if (key.key == MLX_KEY_D)
	{
		new_y += sin(all_data->player->direction - PI * 90 / 180) * -STEP;
		new_x += cos(all_data->player->direction - PI * 90 / 180) * -STEP;
	}
	if (key.key == MLX_KEY_LEFT)
		all_data->player->direction -= STEP;
	if (key.key == MLX_KEY_RIGHT)
		all_data->player->direction += STEP;
	check_valid_movements(new_y, new_x, all_data);
	cast_rays(all_data);
	ft_cub3D(all_data);
}

int	main(void)
{
	t_all_data *all_data;

	all_data = init_all_data();
	mlx_image_to_window(all_data->mlx, all_data->image, 0, 0);
	mlx_key_hook(all_data->mlx, key_hook, (void *)all_data);
	ft_cub3D(all_data);
	mlx_loop(all_data->mlx);
}