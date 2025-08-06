#include "include/cub3D_bonus.h"

int	main(int argc, char **argv)
{
	t_all_data	*all_data;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (EXIT_FAILURE);
	}
	all_data = init_all_data(argv[1]);
	init_input_state(all_data);
	mlx_set_cursor_mode(all_data->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(all_data->mlx, mouse_move_hook, (void *)all_data);
	mlx_key_hook(all_data->mlx, key_press_hook, (void *)all_data);
	mlx_loop_hook(all_data->mlx, game_loop, (void *)all_data);
	cast_rays(all_data);
	render(all_data);
	mlx_loop(all_data->mlx);
	mlx_terminate(all_data->mlx);
	free_all_data(all_data);
}
