#include "include/cub3D.h"

double	handle_input(t_all_data *all_data, t_keys key)
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
	double		move_direction;

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

int	main(int argc, char **argv)
{
	t_all_data	*all_data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (EXIT_FAILURE);
	}
	all_data = init_all_data(argv[1]);
	mlx_key_hook(all_data->mlx, key_hook, (void *)all_data);
	cast_rays(all_data);
	ft_cub3d(all_data);
	mlx_loop(all_data->mlx);
}
